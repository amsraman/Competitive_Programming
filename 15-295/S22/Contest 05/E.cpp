#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, s, ct, ans;
vector<int> g[5000];
bool vis[5000], cv[5000];

void dfs1(int x) {
    vis[x] = true;
    for(int u: g[x]) {
        if(!vis[u]) {
            dfs1(u);
        }
    }
}

void dfs2(int x) {
    ++ct, cv[x] = true;
    for(int u: g[x]) {
        if(!vis[u] && !cv[u]) {
            dfs2(u);
        }
    }
}

int main() {
    cin >> n >> m >> s;
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
    }
    dfs1(s - 1);
    vector<pair<int, int>> vs;
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            ct = 0;
            dfs2(i);
            vs.push_back({ct, i});
            for(int j = 0; j < n; j++) {
                cv[j] = false;
            }
        }
    }
    sort(vs.begin(), vs.end());
    reverse(vs.begin(), vs.end());
    for(pair<int, int> v: vs) {
        if(!vis[v.s]) {
            ++ans;
            dfs1(v.s);
        }
    }
    cout << ans << endl;
}