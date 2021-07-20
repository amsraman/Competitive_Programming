#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 1e9 + 7;

int n, m, a[500000], dp[500000][2], ans = 1;

int mul(int x, int y) {
    return ((ll) x * y) % mod;
}

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y&1) {
            ret = mul(ret, x);
        }
        x = mul(x, x), y >>= 1;
    }
    return ret;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i<n; i++) {
        cin >> a[i];
    }
    dp[0][0] = m - 1;
    dp[0][1] = 0;
    for(int i = 1; i < n; i++) {
        dp[i][0] = (mul(dp[i-1][0], m - 2) + mul(dp[i-1][1], m - 1)) % mod;
        dp[i][1] = dp[i-1][0];
    }
    for(int i = 0, lst = -1; i<n; i++) {
        if(a[i] == 0 && (i == n-1 || a[i+1] > 0)) {
            if(lst == -1 && i == n-1) {
                ans = mul(m, exp(m - 1, n - 1));
            } else if(lst == -1 || i == n-1) {
                ans = mul(ans, exp(m - 1, i - lst));
            } else if(a[lst] == a[i+1]) {
                ans = mul(ans, dp[i-lst-1][0]);
            } else {
                int num = (dp[i-lst-1][1] + mul(dp[i-lst-1][0], mul(m - 2, exp(m - 1, mod - 2)))) % mod;
                ans = mul(ans, num);
            }
        }
        if(a[i] > 0) {
            lst = i;
        }
    }
    cout << ans << endl;
}
