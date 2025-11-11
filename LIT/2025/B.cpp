#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<string> grid(n), rg(n);
        int ones = 0;
        for(int i = 0; i < n; i++) {
            cin >> grid[i];
            for(char c: grid[i]) {
                ones += c - '0';
            }
            rg[i] = string(n, '.');
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                rg[j][n - i - 1] = grid[i][j];
            }
        }
        auto is_eq = [&](int x, int y, int nx, int ny) {
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) return false;
            return grid[x][y] == rg[nx][ny];
        };
        int res = ones;
        for(int dx = -n; dx <= n; dx++) {
            for(int dy = -n; dy <= n; dy++) {
                int num_eq = 0;
                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < n; j++) {
                        if(grid[i][j] != '1') continue;
                        num_eq += (int) is_eq(i, j, i + dx, j + dy);
                    }
                }
                res = min(res, ones - num_eq);
            }
        }
        cout << res << '\n';
    }
}