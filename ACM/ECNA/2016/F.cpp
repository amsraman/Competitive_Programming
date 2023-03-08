#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    while(n != 0) {
        vector<int> nums(n, 0);
        for(int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 1e9));
        for(int i = 0; i < n; i++) {
            dp[i][(i + 1) % n] = 0;
        }
        for(int len = 2; len < n; len++) {
            for(int i = 0, j = (i + len) % n; i < n; i++, j = (j + 1) % n) {
                for(int k = (i + 1) % n; k != j; k = (k + 1) % n) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
                dp[i][j] += __gcd(nums[i], nums[j]);
            }
        }
        int ans = 1e9;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                ans = min(ans, dp[i][j] + dp[j][i] + __gcd(nums[i], nums[j]));
            }
        }
        cout << ans << '\n';
        cin >> n;
    }
}
