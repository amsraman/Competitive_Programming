#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, cc, ans1 = 0, ans2 = 0; cin >> n >> m;
    vector<string> grid(n);
    cin.ignore();
    for(int i = 0; i < n; i++) {
        getline(cin, grid[i]);
    }
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool fd;
    auto ok = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m && grid[x][y] != 'X';
    };
    auto dfs = [&](auto rec, int x, int y) -> void {
        if(grid[x][y] != '.' && grid[x][y] != ' ') {
            fd = true;
            return;
        }
        vis[x][y] = true, cc += grid[x][y] == '.';
        for(auto [dx, dy]: dirs) {
            if(ok(x + dx, y + dy) && !vis[x + dx][y + dy]) {
                rec(rec, x + dx, y + dy);
            }
        }
    };
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(vis[i][j] || (grid[i][j] != '.' && grid[i][j] != ' ')) continue;
            fd = false, cc = 0;
            dfs(dfs, i, j);
            if(fd && cc > 0) ++ans1;
            else ans2 += cc;
        }
    }
    cout << ans1 << " " << ans2 << '\n';
}