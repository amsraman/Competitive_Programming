#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("zone_in_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int r, c, s; cin >> r >> c >> s; ++s;
        vector<string> grid(r);
        for(int i = 0; i < r; i++) {
            cin >> grid[i];
        }
        queue<pair<int, int>> q;
        for(int i = 0; i < r; i++) {
            q.emplace(i, -1); q.emplace(i, c);
        }
        for(int i = 0; i < c; i++) {
            q.emplace(-1, i); q.emplace(r, i);
        }
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        auto ok = [&](int x, int y) {
            return x >= 0 && x < r && y >= 0 && y < c;
        };
        vector<vector<int>> dist(r, vector<int>(c, -1));
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(grid[i][j] == '.') continue;
                q.emplace(i, j); dist[i][j] = 0;
            }
        }
        while(!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            int cur_d = ok(x, y) ? dist[x][y] : 0;
            for(auto [dx, dy]: dirs) {
                if(ok(x + dx, y + dy) && dist[x + dx][y + dy] == -1) {
                    dist[x + dx][y + dy] = cur_d + 1;
                    q.emplace(x + dx, y + dy);
                }
            }
        }
        int res = 0;
        vector<vector<bool>> vis(r, vector<bool>(c, false));
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(vis[i][j] || dist[i][j] < s) continue;
                q.emplace(i, j); vis[i][j] = true; int cur = 0;
                while(!q.empty()) {
                    auto [x, y] = q.front(); q.pop();
                    ++cur;
                    for(auto [dx, dy]: dirs) {
                        if(ok(x + dx, y + dy) && dist[x + dx][y + dy] >= s && !vis[x + dx][y + dy]) {
                            q.emplace(x + dx, y + dy);
                            vis[x + dx][y + dy] = true;
                        }
                    }
                }
                res = max(res, cur);
            }
        }
        cout << "Case #" << _ << ": " << res << '\n';
    }
}