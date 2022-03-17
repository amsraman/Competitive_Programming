#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, cal[100], cl[101], dp[101][101][2], ans;

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> cal[i];
    }
    cl[0] = m;
    for(int i = 1; i <= n; i++) {
        cl[i] = cl[i - 1] * 2 / 3;
    }
    for(int i = 0; i <= 100; i++) {
        for(int j = 0; j <= 100; j++) {
            for(int k = 0; k < 2; k++) {
                dp[i][j][k] = -INF;
            }
        }
    }
    dp[0][0][0] = 0; 
    for(int i = 0; i < n; i++) {
        dp[i + 1][0][0] = dp[i][0][0];
        for(int j = 0; j < n; j++) {
            // We take
            dp[i + 1][j + 1][0] = max(dp[i + 1][j + 1][0], dp[i][j][0] + min(cl[j], cal[i]));
            if(j > 0) {
                dp[i + 1][j][0] = max(dp[i + 1][j][0], dp[i][j][1] + min(cl[j - 1], cal[i]));
            }
            // We stay
            dp[i + 1][j][1] = max(dp[i + 1][j][1], dp[i][j][0]);
            dp[i + 1][0][0] = max(dp[i + 1][0][0], dp[i][j][1]);
        }
    }
    for(int i = 0; i <= n; i++) {
        ans = max({ans, dp[n][i][0], dp[n][i][1]});
    }
    cout << ans << endl;
}