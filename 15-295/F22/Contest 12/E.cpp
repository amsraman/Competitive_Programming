#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n); string s;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> s;
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n + 1, -0x3f3f3f3f)));
    vector<vector<int>> dp2(n, vector<int>(n, 0));
    for(int i = n - 1; i >= 0; i--) {
        if(a[0] >= 0) dp[i][i][0] = a[0];
        dp[i][i][1] = 0;
        if(i < n - 1) {
            if(s[i] == s[i + 1]) dp[i][i + 1][2] = 0;
            if(a[0] >= 0 && i < n - 1) dp[i][i + 1][1] = a[0];
            if(a[1] >= 0 && s[i] == s[i + 1]) dp[i][i + 1][0] = a[1];
        }
        for(int j = i + 2; j < n; j++) {
            for(int k = 1; k <= n; k++) {
                for(int md = i; md < j; md++) {
                    dp[i][j][k] = max({dp[i][j][k], dp[i][md][0] + dp[md + 1][j][k], dp[i][md][k] + dp[md + 1][j][0]});
                }
                if(s[i] == s[j] && k >= 2) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i + 1][j - 1][k - 2]);
                }
                if(a[k - 1] >= 0) {
                    dp[i][j][0] = max(dp[i][j][0], dp[i][j][k] + a[k - 1]);
                }
            }
        }
    }
    int ans = 0;
    for(int i = n - 1; i >= 0; i--) {
        for(int j = i; j < n; j++) {
            dp2[i][j] = max(dp2[i][j], dp[i][j][0]);
            for(int k = i; k < j; k++) {
                dp2[i][j] = max(dp2[i][j], dp2[i][k] + dp2[k + 1][j]);
            }
            ans = max(ans, dp2[i][j]);
        }
    }
    cout << ans << endl;
}