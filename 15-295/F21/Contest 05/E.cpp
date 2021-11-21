#include <bits/stdc++.h>

using namespace std;

int n, c[300000], df[300000], nxt[500000][26], val[300000], ans1, ans2;
string lt;
vector<int> g[300000];

void add_trie(int t1, int t2) {
    for(int i = 0; i < 26; i++) {
        if(nxt[t2][i] == 0) {
            continue;
        }
        if(nxt[t1][i] == 0) {
            nxt[t1][i] = nxt[t2][i];
            df[t1 - 1] += df[nxt[t2][i] - 1];
        } else {
            df[t1 - 1] -= df[nxt[t1][i] - 1];
            add_trie(nxt[t1][i], nxt[t2][i]);
            df[t1 - 1] += df[nxt[t1][i] - 1];
        }
    }
}

void dfs(int x, int p) {
    df[x] = 1;
    for(int i: g[x]) {
        if(i != p) {
            dfs(i, x);
            if(nxt[x + 1][(lt[i] - 'a')] == 0) {
                nxt[x + 1][(lt[i] - 'a')] = i + 1;
                df[x] += df[i];
            } else {
                df[x] -= df[nxt[x + 1][(lt[i] - 'a')] - 1];
                add_trie(nxt[x + 1][(lt[i] - 'a')], i + 1);
                df[x] += df[nxt[x + 1][(lt[i] - 'a')] - 1];
            }
        }
    }
    val[x] = c[x] + df[x];
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> c[i];
    }
    cin >> lt;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs(0, 0);
    int ans1 = 0, ans2 = 0;
    for(int i = 0; i < n; i++) {
        ans1 = max(ans1, val[i]);
    }
    for(int i = 0; i < n; i++) {
        if(val[i] == ans1) {
            ++ans2;
        }
    }
    cout << ans1 << endl << ans2 << endl;
}