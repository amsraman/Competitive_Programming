#include <bits/stdc++.h>

using namespace std;

namespace Combo {
    const int mod = 1e9 + 7;
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
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> b(n + 2, 0); b[n + 1] = 1;
    for(int i = 0; i < n; i++) {
        cin >> b[i + 1]; b[i + 1] += 2;
    }
    n += 2;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int i = n - 1; i >= 0; i--) {
        dp[i][i + 1] = 1;
        for(int j = i + 2; j < n; j++) {
            for(int k = i + 1; k < j; k++) {
                int one = k - i - 1, two = j - k - 1;
                int ways = mul(mul(ncr(one + two, one), dp[i][k]), dp[k][j]);
                if(b[k] == b[i] + 1) dp[i][j] = (dp[i][j] + ways) % mod;
                if(b[k] == b[j] + 1) dp[i][j] = (dp[i][j] + ways) % mod;
            }
        }
    }
    int res = dp[0][n - 1], nz = 0;
    for(int i = 0; i < n; i++) nz += b[i] == 2;
    if(nz != 1) res = 0;
    cout << res << '\n';
}