#include <bits/stdc++.h>

using namespace std;

namespace Combo {
    const int mod = 998244353;
    vector<int> f = {1}, invf = {1};
    int mul(int x, int y) {
        return (1LL * x * y) % mod;
    }
    int exp(int x, int y) {
        int ret = 1;
        while(y) {
            if(y & 1) ret = mul(ret, x);
            x = mul(x, x), y >>= 1;
        }
        return ret;
    }
    int fact(int x) {
        if(x < 0) return 0;
        while(x >= f.size()) {
            f.push_back(mul(f.size(), f.back()));
        }
        return f[x];
    }
    int ifact(int x) {
        if(x < 0) return 0;
        while(x >= invf.size()) {
            invf.push_back(mul(exp(invf.size(), mod - 2), invf.back()));
        }
        return invf[x];
    }
    int inv(int x) {
        return mul(fact(x - 1), ifact(x));
    }
    int ncr(int x, int y) {
        if(x < y || x < 0) return 0;
        return mul(fact(x), mul(ifact(x - y), ifact(y)));
    }
}
 
using namespace Combo;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> dp(101, vector<int>(101, 0));
    for(int i = 0; i <= 100; i++) {
        dp[i][i] = 1;
        for(int j = 0; j < i; j++) {
            for(int k = 0; k <= j; k++) {
                dp[i][j] = (dp[i][j] + mul(dp[i - k - 1][j - k], dp[i - 1][k])) % mod;
            }
        }
    }
    int res = 1;
    for(int i = 1; i < n; i++) {
        res = mul(res, dp[a[i]][a[i] - a[i - 1]]);
    }
    cout << res << '\n';
}
/*
dp[i][j] = how many ways can 2^i be written as the sum of powers of 2 <= 2^j
*/