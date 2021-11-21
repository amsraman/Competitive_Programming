#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int n, a[200000], num[1000001], pow2[1000001], dp[1000001], ans;

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        for(int j = 1; j * j <= a[i]; j++) {
            if(a[i] % j == 0) {
                ++num[j];
                if(j != a[i] / j) {
                    ++num[a[i] / j];
                }
            }
        }
    }
    pow2[0] = 1;
    for(int i = 1; i <= 1e6; i++) {
        pow2[i] = mul(pow2[i - 1], 2);
    }
    for(int i = 1e6; i > 1; i--) {
        dp[i] = (num[i] == 0 ? 0 : mul(num[i], pow2[num[i] - 1]));
        for(int j = 2 * i; j <= 1e6; j += i) {
            dp[i] = (dp[i] - dp[j] + mod) % mod;
        }
        ans = (ans + mul(dp[i], i)) % mod;
    }
    cout << ans << endl;
}