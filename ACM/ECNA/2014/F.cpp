#include <bits/stdc++.h>

using namespace std;

int main() {
    map<char, pair<int, int>> dirs = {{'N', {-1, 0}}, {'S', {1, 0}}, {'E', {0, 1}}, {'W', {0, -1}}};
    int n, m; cin >> n >> m;
    for(int _ = 1; n != 0 || m != 0; _++) {
        vector<vector<string>> grid(n, vector<string>(m));
        vector<int> dist(n * m, 1e9); vector<bool> vis(n * m, false);
        vector<int> nxt(n * m, -1); vector<vector<int>> g(n * m);
        for(int i = 0; i < n * m - 1; i++) cin >> grid[i / m][i % m];
        auto conv = [&](int x, int y) {
            return m * x + y;
        };
        auto ok = [&](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < m;
        };
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(i * m + j == n * m - 1) continue;
                int num = atoi(grid[i][j].substr(0, grid[i][j].length() - 1).c_str());
                pair<int, int> dir = dirs[grid[i][j].back()];
                dir.first *= num, dir.second *= num;
                if(ok(i + dir.first, j + dir.second)) {
                    nxt[conv(i, j)] = conv(i + dir.first, j + dir.second);
                    g[conv(i + dir.first, j + dir.second)].push_back(conv(i, j));
                }
            }
        }
        queue<int> q; q.push(n * m - 1); dist[n * m - 1] = 0;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v: g[u]) {
                if(dist[v] == 1e9) {
                    dist[v] = dist[u] + 1; q.push(v);
                }
            }
        }
        tuple<int, int, int, string> ans = {dist[0], 1e9, 1e9, ""};
        for(int cur = 0, step = 0; cur != -1 && !vis[cur]; cur = nxt[cur], step++) {
            int row = cur / m, col = cur % m; vis[cur] = true;
            for(int i = 0; i < n; i++) {
                char dir = (i < row ? 'N' : 'S');
                ans = min(ans, {step + dist[conv(i, col)] + 1, row, col, to_string(abs(row - i)) + dir});
            }
            for(int i = 0; i < m; i++) {
                char dir = (i < col ? 'W' : 'E');
                ans = min(ans, {step + dist[conv(row, i)] + 1, row, col, to_string(abs(col - i)) + dir});
            }
        }
        cout << "Case " << _ << ": ";
        if(get<0>(ans) == 1e9) {
            cout << "impossible\n";
        } else if(get<0>(ans) == dist[0]) {
            cout << "none " << dist[0] << '\n';
        } else {
            cout << get<1>(ans) << " " << get<2>(ans) << " " << get<3>(ans) << " " << get<0>(ans) << '\n';
        }
        cin >> n >> m;
    }
}