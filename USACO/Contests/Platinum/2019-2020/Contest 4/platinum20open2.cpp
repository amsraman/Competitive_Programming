#include <bits/stdc++.h>

using namespace std;

int n, m, prime[7501], fact[7501], ncr[7501][7501], dp[7501], ndp[7501], ans = 1;

int mul(int x, int y, int mod) {
    return (1LL * x * y) % mod;
}

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret = mul(ret, x, m);
        }
        x = mul(x, x, m), y >>= 1;
    }
    return ret;
}

int main() {
    ifstream cin("exercise.in");
    ofstream cout("exercise.out");
    cin >> n >> m;
    for(int i = 2; i <= n; i++) {
        if(prime[i] == 0) {
            for(int j = 2 * i; j <= n; j += i) {
                prime[j] = -1;
            }
            for(int j = i; j <= n; j *= i) {
                prime[j] = i;
            }
        }
    }
    fact[0] = ncr[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i, m - 1);
        ncr[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            ncr[i][j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % (m - 1);
        }
    }
    for(int d = 1; d <= n; d++) {
        if(prime[d] > 0) {
            dp[0] = 1;
            for(int i = 1; i <= n / d; i++) {
                dp[i] = 0;
                for(int j = 0; j < i; j++) {
                    int diff = (i - j) * d;
                    dp[i] = (dp[i] + mul(dp[j], mul(fact[diff - 1], ncr[i * d - 1][diff - 1], m - 1), m - 1)) % (m - 1);
                }
            }
            for(int i = n / d; i >= 0; i--) {
                ndp[i] = fact[n - d * i];
                for(int j = i + 1; j <= n / d; j++) {
                    ndp[i] = (ndp[i] - mul(ndp[j], mul(dp[j - i], ncr[n - d * i][(j - i) * d], m - 1), m - 1) + (m - 1)) % (m - 1);
                }
            }
            int acc = 0;
            for(int i = 1; i <= n / d; i++) {
                acc = (acc + mul(mul(dp[i], ndp[i], m - 1), ncr[n][d * i], m - 1)) % (m - 1);
            }
            ans = mul(ans, exp(prime[d], acc), m);
        }
    }
    cout << ans << endl;
}