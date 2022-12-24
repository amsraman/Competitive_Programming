#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> topo;
vector<bool> vis;

void dfs(int u) {
    vis[u] = true;
    for(int v: g[u]) {
        if(!vis[v]) {
            dfs(v);
        }
    }
    topo.push_back(u);
}

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, ans = 1;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        g.resize(n), vis.resize(n, false);
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            if(a[u - 1] > a[v - 1]) {
                g[u - 1].push_back(v - 1);
            } else if(a[u - 1] < a[v - 1]) {
                g[v - 1].push_back(u - 1);
            }
        }
        for(int i = 0; i < n; i++) {
            if(!vis[i]) {
                dfs(i);
            }
        }
        vector<int> dp(n, 1);
        for(int u: topo) {
            for(int v: g[u]) {
                dp[u] += dp[v];
            }
            ans = max(ans, dp[u]);
        }
        cout << "Case #" << _ << ": " << ans << endl;
        g.clear(), vis.clear(), topo.clear();
    }
}