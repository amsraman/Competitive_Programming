#include <bits/stdc++.h>

using namespace std;

int n, d, mod, dp[1001][11][1001], inv[11], ans;

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

int binom(int x, int y) {
    int ret = 1;
    for(int i = 0; i < y; i++) {
        ret = mul(ret, mul(x - i + mod, inv[i + 1]));
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> d >> mod;
    for(int i = 1; i <= d; i++) {
        inv[i] = exp(i, mod - 2);
    }
    for(int i = 0; i <= n; i++) {
        dp[1][0][i] = 1;
    }
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= d; j++) {
            for(int k = 1; k <= n; k++) {
                for(int l = 0; (l <= j && l * k <= i - 1); l++) {
                    dp[i][j][k] = (dp[i][j][k] + mul(binom(((k == 1 ? 1 : dp[k][d - 1][n]) + l - 1) % mod, l), dp[i - l * k][j - l][k - 1])) % mod;
                }
            }
        }
    }
    ans = dp[n][d][(n - 1) / 2];
    if(n % 2 == 0) {
        ans = (ans + binom(dp[n / 2][d - 1][n / 2] + 1, 2)) % mod;
    }
    cout << (n <= 2 ? 1 : ans) << '\n';
}