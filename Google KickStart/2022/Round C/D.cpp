#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret = mul(ret, x);
        }
        x = mul(x, x), y >>= 1;
    }
    return ret;
}

int main() {
    vector<vector<int>> ncr(401, vector<int>(401, 0));
    for(int i = 0; i <= 400; i++) {
        ncr[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            ncr[i][j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % mod;
        }
    }
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n;
        string s;
        cin >> n >> s;
        int ans = 0;
        for(int i = 0, j = n - 1; i < j; i++, j--) {
            if(s[i] != s[j]) {
                ans = 1;
                break;
            }
        }
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, 0)));
        for(int i = n - 1; i >= 0; i--) {
            for(int j = i; j < n; j++) {
                dp[i][j][0] = j - i + 1;
            }
        }
        for(int k = 1; k < n; k++) {
            for(int i = n - 1; i >= 0; i--) {
                for(int j = i + 1; j < n; j++) {
                    dp[i][j][k] = (dp[i + 1][j][k] + dp[i][j - 1][k]) % mod;
                    dp[i][j][k] = (dp[i][j][k] - dp[i + 1][j - 1][k] + mod) % mod;
                    if(s[i] == s[j]) {
                        int extra = (k == 1 ? 1 : dp[i + 1][j - 1][k - 2]);
                        dp[i][j][k] = (dp[i][j][k] + extra) % mod;
                    }
                }
            }
        }
        for(int i = 0; i < n; i++) {
            int ichoose = exp(ncr[n][i + 1], mod - 2);
            ans = (ans + mul(ichoose, dp[0][n - 1][i])) % mod;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}