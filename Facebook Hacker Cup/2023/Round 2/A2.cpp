#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("ready_go_part_2_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int r, c; cin >> r >> c;
        vector<string> grid(r);
        for(int i = 0; i < r; i++) {
            cin >> grid[i];
        }
        vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        auto ok = [&](int x, int y) {
            return x >= 0 && x < r && y >= 0 && y < c;
        };
        int ans = 0;
        vector<vector<int>> num(r, vector<int>(c, 0));
        vector<vector<bool>> vis(r, vector<bool>(c, false));
        set<pair<int, int>> emp; int ct = 0;
        auto bfs = [&](int x, int y) -> void {
            vis[x][y] = true;
            queue<pair<int, int>> q; q.push({x, y}); vis[x][y] = true;
            while(!q.empty()) {
                auto [x, y] = q.front(); q.pop(); ++ct;
                for(auto [dx, dy]: dir) {
                    if(ok(x + dx, y + dy) && !vis[x + dx][y + dy] && grid[x + dx][y + dy] == 'W') {
                        q.push({x + dx, y + dy});
                        vis[x + dx][y + dy] = true;
                    }
                    if(ok(x + dx, y + dy) && grid[x + dx][y + dy] == '.') emp.insert({x + dx, y + dy});
                }
            }
        };
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(vis[i][j] || grid[i][j] != 'W') continue;
                bfs(i, j);
                if(emp.size() == 1) {
                    auto [x, y] = *emp.begin();
                    num[x][y] += ct;
                }
                emp.clear(); ct = 0;
            }
        }
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                ans = max(ans, num[i][j]);
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}