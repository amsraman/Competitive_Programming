#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    while(n > 0) {
        vector<string> grid(n);
        for(int i = 0; i < n; i++) {
            cin >> grid[i];
        }
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        auto ok = [&](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < m;
        };
        vector<vector<int>> deg(n, vector<int>(m, 0));
        vector<pair<int, int>> one;
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < m; y++) {
                for(auto [dx, dy]: dirs) {
                    if(ok(x + dx, y + dy) && grid[x + dx][y + dy] == '1') {
                        ++deg[x][y];
                    }
                }
                if(grid[x][y] == '1' && deg[x][y] <= 1) one.emplace_back(x, y);
            }
        }
        int ans = 0;
        for(auto [x, y]: one) {
            if(vis[x][y]) continue;
            vector<pair<int, int>> ends;
            queue<pair<int, int>> q;
            q.push({x, y}); vis[x][y] = true;
            while(!q.empty()) {
                tie(x, y) = q.front(); q.pop();
                if(deg[x][y] <= 1) {
                    ends.emplace_back(x, y);
                }
                for(auto [dx, dy]: dirs) {
                    if(ok(x + dx, y + dy) && !vis[x + dx][y + dy] && grid[x + dx][y + dy] == '1' && deg[x + dx][y + dy] <= 2) {
                        q.push({x + dx, y + dy});
                        vis[x + dx][y + dy] = true;
                    }
                }
            }
            bool maximal = (int) ends.size() == 2;
            if((int) ends.size() == 1 && deg[ends[0].first][ends[0].second] == 0) maximal = true;
            for(auto [x, y]: ends) {
                for(auto [dx, dy]: dirs) {
                    if(ok(x + dx, y + dy) && grid[x + dx][y + dy] == '0' && deg[x + dx][y + dy] == 1) {
                        maximal = false;
                    }
                }
            }
            ans += (int) maximal;
        }
        cout << ans << '\n';
        cin >> n >> m;
    }
}