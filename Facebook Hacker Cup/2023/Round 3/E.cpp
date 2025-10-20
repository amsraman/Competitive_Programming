#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int main() {
    ifstream cin("similar_ships_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<vector<int>> g(n);
        for(int i = 1, p; i < n; i++) {
            cin >> p; --p;
            g[p].push_back(i); g[i].push_back(p);
        }
        auto bfs = [&](int s) -> pair<int, int> { // furthest dist, vertex
            queue<int> q; q.push(s);
            vector<int> dist(n, -1); dist[s] = 0;
            while(!q.empty()) {
                int u = q.front(); q.pop();
                for(int v: g[u]) {
                    if(dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                }
            }
            pair<int, int> res = {0, s};
            for(int i = 0; i < n; i++) {
                res = max(res, {dist[i], i});
            }
            return res;
        };
        auto [d1, v1] = bfs(0);
        auto [d2, v2] = bfs(v1);
        int ans = 0;
        for(int i = 0; i <= d2; i++) {
            ans = (ans + (n - i)) % mod;
        }
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}