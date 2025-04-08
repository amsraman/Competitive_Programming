#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, a, b; cin >> n >> m >> a >> b; --a, --b;
    vector<vector<int>> dist(n, vector<int>(n, 1e9));
    vector<tuple<int, int, int>> roads;
    for(int i = 0, i1, i2, l; i < m; i++) {
        cin >> i1 >> i2 >> l; --i1, --i2;
        dist[i1][i2] = dist[i2][i1] = l;
        roads.emplace_back(i1, i2, l);
    }
    for(int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    int ans = 0;
    for(auto [u, v, l]: roads) {
        bool pave = (dist[a][u] + l + dist[v][b] == dist[a][b] || dist[a][v] + l + dist[u][b] == dist[a][b]);
        if(!pave) {
            ans += l;
        }
    }
    cout << ans << '\n';
}