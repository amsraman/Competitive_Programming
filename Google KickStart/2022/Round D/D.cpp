#include <bits/stdc++.h>

using namespace std;

int n, m, k;
vector<int> topo;
vector<bool> gg, good;
vector<vector<int>> g;
vector<set<int>> vis;

void dfs1(int u) {
    gg[u] = true;
    for(int v: g[u]) {
        if(!gg[v]) {
            dfs1(v);
        }
    }
    topo.push_back(u);
}

void dfs2(int og, int u) {
    if(vis[og].size() > k) {
        return;
    }
    vis[og].insert(u);
    for(int v: g[u]) {
        if(!vis[og].count(v)) {
            dfs2(og, v);
            if(vis[og].size() > k) {
                return;
            }
        }
    }
}

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> m >> k;
        g.resize(n), vis.resize(n), gg.resize(n, false), good.resize(n, false);
        for(int i = 0, a, b; i < m; i++) {
            cin >> a >> b;
            g[b - 1].push_back(a - 1);
        }
        for(int i = 0; i < n; i++) {
            if(!gg[i]) {
                dfs1(i);
            }
        }
        gg.clear(), gg.resize(n, false);
        for(int i: topo) {
            if(!gg[i]) {
                for(int j: g[i]) {
                    if(good[j]) {
                        good[i] = true;
                    }
                }
                if(good[i]) {
                    gg[i] = true;
                    continue;
                }
                vis[i].insert(i);
                dfs2(i, i);
                if(vis[i].size() > k) {
                    good[i] = true;
                }
                gg[i] = true;
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++) {
            ans += (int) good[i];
        }
        cout << "Case #" << _ << ": " << ans << endl;
        topo.clear(), good.clear(), g.clear(), gg.clear(), vis.clear();
    }
}