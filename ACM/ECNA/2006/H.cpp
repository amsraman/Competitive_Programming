#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    for(int _ = 1; n > 0; _++) {
        vector<string> grid(n);
        vector<pair<int, int>> emp;
        for(int i = 0; i < n; i++) {
            cin >> grid[i];
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == '.') {
                    emp.emplace_back(i, j);
                }
            }
        }
        int sz = (int) emp.size(), num_states = 1;
        for(int i = 0; i < sz; i++) num_states *= 3;
        vector<int> dp(num_states);
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        int player = (n * n - sz) % 2;
        for(int i = 0; i < 1 << sz; i++) { // try all fills
            int res1 = 0, res2 = 0, ct;
            for(int j = 0; j < sz; j++) {
                auto [x, y] = emp[j];
                grid[x][y] = char('0' + ((i >> j) & 1));
            }
            // logic to see who won
            auto dfs = [&](auto rec, int x, int y) -> void {
                vis[x][y] = true; ++ct;
                for(auto [dx, dy]: dirs) {
                    if(x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < n && !vis[x + dx][y + dy] && grid[x + dx][y + dy] == grid[x][y]) {
                        rec(rec, x + dx, y + dy);
                    }
                }
            };
            for(int x = 0; x < n; x++) {
                for(int y = 0; y < n; y++) {
                    if(!vis[x][y]) {
                        ct = 0;
                        dfs(dfs, x, y);
                        if(grid[x][y] == char('0' + player)) {
                            res1 = max(res1, ct);
                        } else {
                            res2 = max(res2, ct);
                        }
                    }
                }
            }
            for(int x = 0; x < n; x++) {
                for(int y = 0; y < n; y++) {
                    vis[x][y] = false;
                }
            }
            int state = 0;
            for(int j = sz - 1; j >= 0; j--) {
                state = 3 * state + ((i >> j) & 1) + 1;
            }
            dp[state] = res1 - res2;
            for(int j = 0; j < sz; j++) {
                auto [x, y] = emp[j];
                grid[x][y] = '.';
            }
        }
        for(int i = num_states - 1; i >= 0; i--) {
            int par = 0, res;
            for(int j = 0, cur = i; j < sz; j++, cur /= 3) {
                par ^= int(cur % 3 == 0);
            }
            if(par == sz % 2) {
                res = -1e9;
            } else {
                res = 1e9;
            }
            for(int j = 0, cur = i, p3 = 1; j < sz; j++, cur /= 3, p3 *= 3) {
                if(cur % 3 == 0) { // there is an empty space here
                    if(par == sz % 2) { // you're going
                        res = max(res, dp[i + (1 + player) * p3]);
                        dp[i] = res;
                    } else { // the opp is going
                        res = min(res, dp[i + (1 + (player ^ 1)) * p3]);
                        dp[i] = res;
                    }
                }
            }
        }
        pair<int, int> mv;
        for(int i = 0, p3 = 1; i < sz; i++, p3 *= 3) {
            if(dp[(1 + player) * p3] == dp[0]) {
                mv = emp[i];
                break;
            }
        }
        cout << "(" << mv.first << "," << mv.second << ") " << dp[0] << '\n';
        cin >> n;
    }
}