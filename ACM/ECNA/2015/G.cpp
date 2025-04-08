#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int m, n; cin >> m >> n;
    vector<vector<bool>> blk(m, vector<bool>(3, false));
    for(int i = 0; i < n; i++) {
        double x, y; cin >> x >> y;
        blk[(int) x][(int) y] = true;
    }
    vector<vector<ll>> dp(3 * m + 1, vector<ll>(8, 0)); dp[0][0] = 1;
    for(int i = 0; i < 3 * m; i++) {
        int row = i / 3, col = i % 3;
        for(int j = 0; j < 8; j++) {
            if(blk[row][col] || ((j >> col) & 1)) { // can't place anything
                dp[i + 1][j & (7 ^ (1 << col))] += dp[i][j];
            } else {
                dp[i + 1][j] += dp[i][j]; // placing a 1x1
                if(row < m - 1 && !blk[row + 1][col]) { // try placing a 1x2
                    dp[i + 1][j ^ (1 << col)] += dp[i][j];
                }
                if(col < 2 && (((j >> (col + 1)) & 1) == 0) && !blk[row][col + 1]) { // try placing a 2x1
                    dp[i + 2][j] += dp[i][j];
                }
            }
        }
    }
    cout << dp[3 * m][0] << '\n';
}