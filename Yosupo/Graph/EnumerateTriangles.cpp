// 109 ms
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

void EnumerateTriangles(const vector<vector<int>> & graph, function<void (int, int, int)> f) {
    int n = graph.size();
    vector<vector<int>> bigger_neighbors(n);
    for(int i = 0; i < n; i++) {
        for(int j: graph[i]) {
            if(graph[j].size() > graph[i].size() || (graph[j].size() == graph[i].size() && j > i)) {
                bigger_neighbors[i].push_back(j);
            }
        }
    }
    vector<bool> neighbor(n, false);
    for(int i = 0; i < n; i++) {
        for(int j: bigger_neighbors[i]) neighbor[j] = true;
        for(int j: bigger_neighbors[i]) {
            for(int k: bigger_neighbors[j]) {
                if(neighbor[k]) {
                    f(i, j, k);
                }
            }
        }
        for(int j: bigger_neighbors[i]) neighbor[j] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, ans = 0;
    cin >> n >> m;
    vector<int> x(n);
    vector<vector<int>> g(n);
    for(int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto f = [&](int a, int b, int c) {
        ans = (ans + (1LL * (1LL * x[a] * x[b] % mod) * x[c] % mod)) % mod;
    };
    EnumerateTriangles(g, f);
    cout << ans << '\n';
}