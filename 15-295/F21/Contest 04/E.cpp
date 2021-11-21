#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int n, m, dp[250][(1 << 15)][2][2], ans;
char grid[250][250];

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    if(n < m) {
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < i; j++) {
                swap(grid[i][j], grid[j][i]);
            }
        }
        swap(n, m);
    }
    if(grid[0][0] == '.') {
        dp[0][1][1][0] = dp[0][0][0][1] = 1;
    } else {
        dp[0][0][0][0] = 1;
    }
    for(int pos = 0; pos < n * m - 1; pos++) {
        for(int k = 0; k < (1 << m); k++) {
            int x_pos = (pos + 1) / m, y_pos = (pos + 1) % m;
            if(grid[x_pos][y_pos] == '.') {
                // Case 1: We don't guard the next cell
                if(y_pos == 0 && ((1 << y_pos) & k)) {
                    for(int x = 0; x < 2; x++) {
                        for(int y = 0; y < 2; y++) {
                            dp[pos + 1][k][0][y] += dp[pos][k][x][y];
                            dp[pos + 1][k][0][y] %= mod;
                        }
                    }
                } else if(y_pos != 0) {
                    for(int x = 0; x < 2; x++) {
                        for(int y = 0; y < 2; y++) {
                            if(x == 0 && !((1 << y_pos) & k)) {
                                continue;
                            }
                            dp[pos + 1][k][x][y] += dp[pos][k][x][y];
                            dp[pos + 1][k][x][y] %= mod;
                        }
                    }
                }
                // Case 2: We do guard the next cell
                for(int x = 0; x < 2; x++) {
                    for(int y = 0; y < 2; y++) {
                        dp[pos + 1][(k | (1 << y_pos))][1][y] += dp[pos][k][x][y];
                        dp[pos + 1][(k | (1 << y_pos))][1][y] %= mod;
                    }
                }
                // Case 3: We choose to exclude the next cell
                if(y_pos == 0 && !(k & (1 << y_pos))) {
                    for(int x = 0; x < 2; x++) {
                        dp[pos + 1][k][0][1] += dp[pos][k][x][0];
                        dp[pos + 1][k][0][1] %= mod;
                    }
                } else if(!(k & (1 << y_pos))) {
                    dp[pos + 1][k][0][1] += dp[pos][k][0][0];
                    dp[pos + 1][k][0][1] %= mod;
                }
            } else {
                for(int x = 0; x < 2; x++) {
                    for(int y = 0; y < 2; y++) {
                        dp[pos + 1][k & ~(1 << y_pos)][0][y] += dp[pos][k][x][y];
                        dp[pos + 1][k & ~(1 << y_pos)][0][y] %= mod;
                    }
                }
            }
        }
    }
    for(int i = 0; i < (1 << m); i++) {
        for(int j = 0; j < 4; j++) {
            ans = (ans + dp[n * m - 1][i][j >> 1][j & 1]) % mod;
        }
    }
    cout << ans << endl;
}