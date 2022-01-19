#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int n, mx, zer, a[100001], fact[100001], ifact[100001];
map<array<int, 51>, int> memo[51];

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret = (1LL * ret * x) % mod;
        }
        x = (1LL * x * x) % mod, y >>= 1;
    }
    return ret;
}

int dp(int rem, array<int, 51> vals, int num_left) {
    if(rem >= mx) {
        return fact[num_left];
    }
    if(memo[rem].count(vals)) {
        return memo[rem][vals];
    }
    int tot = 0;
    for(int i = 1; i <= min(mx, rem); i++) {
        if(vals[i] > 0) {
            --vals[i];
            tot = (tot + ((1LL * (vals[i] + 1) * dp(rem + i, vals, num_left - 1)) % mod)) % mod;
            ++vals[i];
        }
    }
    return memo[rem][vals] = tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    array<int, 51> vals;
    vals.fill(0);
    for(int i = 0; i <= n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
        if(i > 0) {
            if(a[i] == 0) {
                ++zer;
            } else {
                ++vals[a[i]];
            }
        }
    }
    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = (1LL * fact[i - 1] * i) % mod;
    }
    ifact[n] = exp(fact[n], mod - 2);
    for(int i = n - 1; i >= 0; i--) {
        ifact[i] = (1LL * ifact[i + 1] * (i + 1)) % mod;
    }
    int npr = (1LL * fact[n] * ifact[n - zer]) % mod;
    cout << (1LL * npr * dp(a[0], vals, n - zer)) % mod << '\n';
}