#include <bits/stdc++.h>

using namespace std;

int main() {
    int r, c, n; cin >> r >> c >> n;
    vector<vector<int>> loc(r, vector<int>(c));
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            cin >> loc[i][j];
        }
    }
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(n + 1, 1e9)));
    for(int i = 0; i < r; i++) {
        if(loc[i][0] == -1) continue;
        dp[i][0][0] = loc[i][0];
    }
    for(int j = 1; j < c; j++) {
        for(int i = 0; i < r; i++) {
            if(loc[i][j] == -1) continue;
            if(i > 0 && i < r - 1 && j > 0 && j < c - 1 && loc[i][j] > max(loc[i][j - 1], loc[i][j + 1]) && loc[i][j] < min(loc[i - 1][j], loc[i + 1][j]) && min(loc[i][j - 1], loc[i][j + 1]) != -1) {
                for(int k = 0; k < n; k++) {
                    for(int dx = -1; dx <= 1; dx++) {
                        if(i + dx >= 0 && i + dx < r) {
                            dp[i][j][k + 1] = min(dp[i][j][k + 1], dp[i + dx][j - 1][k] + loc[i][j]);
                        }
                    }
                }
            } else {
                for(int k = 0; k <= n; k++) {
                    for(int dx = -1; dx <= 1; dx++) {
                        if(i + dx >= 0 && i + dx < r) {
                            dp[i][j][k] = min(dp[i][j][k], dp[i + dx][j - 1][k] + loc[i][j]);
                        }
                    }
                }
            }
        }
    }
    int ans = 1e9;
    for(int i = 0; i < r; i++) {
        ans = min(ans, dp[i][c - 1][n]);
    }
    if(ans == 1e9) {
        cout << "impossible\n";
    } else {
        cout << ans << '\n';
    }
}