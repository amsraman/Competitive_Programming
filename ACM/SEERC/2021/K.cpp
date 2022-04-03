#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, mn[200000];
vector<int> g[200000], ans;

void dfs1(int x, int p) {
    mn[x] = n + 1;
    for(int u: g[x]) {
        if(u != p) {
            dfs1(u, x);
            mn[x] = min(mn[x], mn[u]);
        }
    }
    if(mn[x] == n + 1) {
        mn[x] = x;
    }
}

int dfs2(int x, int p) {
    int wc = -1;
    for(int u: g[x]) {
        if(u != p && (wc == -1 || mn[u] > mn[wc])) {
            wc = u;
        }
    }
    if(wc == -1 || mn[wc] < x) {
        return x;
    }
    return dfs2(wc, x);
}

void dfs3(int x, int p) {
    vector<pair<int, int>> ch;
    for(int u: g[x]) {
        if(u != p) {
            ch.push_back({mn[u], u});
        }
    }
    sort(ch.begin(), ch.end());
    for(pair<int, int> u: ch) {
        dfs3(u.s, x);
    }
    ans.push_back(x + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        int mnl = -1;
        for(int i = 0; i < n; i++) {
            if(g[i].size() == 1) {
                mnl = i;
                break;
            }
        }
        dfs1(g[mnl][0], mnl);
        int root = dfs2(g[mnl][0], mnl);
        dfs1(root, root);
        dfs3(root, root);
        for(int a: ans) {
            cout << a << " ";
        }
        cout << '\n';
        for(int i = 0; i < n; i++) {
            g[i].clear();
        }
        ans.clear();
    }
}