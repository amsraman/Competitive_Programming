// 468 ms
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, ans = 0;
    cin >> n >> m;
    vector<int> x(n), deg(n, 0);
    vector<vector<int>> g(n);
    vector<unordered_set<int>> adj(n);
    for(int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v), adj[u].insert(v);
        g[v].push_back(u), adj[v].insert(u);
        ++deg[u], ++deg[v];
    }
    for(int i = 0; i < n; i++) {
        vector<int> bigger;
        for(int j: g[i]) {
            if(deg[j] > deg[i] || (deg[j] == deg[i] && j > i)) {
                bigger.push_back(j);
            }
        }
        for(int u: bigger) {
            for(int v: bigger) {
                if(u > v && adj[u].count(v)) {
                    ans = (ans + (1LL * (1LL * x[i] * x[u] % mod) * x[v] % mod)) % mod;
                }
            }
        }
    }
    cout << ans << '\n';
}