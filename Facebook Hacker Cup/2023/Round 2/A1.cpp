#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("ready_go_part_1_input.txt");
    ofstream cout("out1.txt");
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
        bool ans = false;
        vector<vector<bool>> vis(r, vector<bool>(c, false));
        set<pair<int, int>> emp;
        auto dfs = [&](auto rec, int x, int y) -> void {
            vis[x][y] = true;
            for(auto [dx, dy]: dir) {
                if(ok(x + dx, y + dy) && !vis[x + dx][y + dy] && grid[x + dx][y + dy] == 'W') {
                    rec(rec, x + dx, y + dy);
                }
                if(ok(x + dx, y + dy) && grid[x + dx][y + dy] == '.') emp.insert({x + dx, y + dy});
            }
        };
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(vis[i][j] || grid[i][j] != 'W') continue;
                dfs(dfs, i, j);
                if(emp.size() == 1) {
                    ans = true;
                }
                emp.clear();
            }
        }
        cout << "Case #" << _ << ": " << (ans ? "YES" : "NO") << '\n';
    }
}