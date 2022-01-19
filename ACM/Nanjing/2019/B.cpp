#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int t, n, m, fact[2000001], ifact[2000001];

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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    fact[0] = 1;
    for(int i = 1; i <= 2e6; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    ifact[2000000] = exp(fact[2000000], mod - 2);
    for(int i = 1999999; i >= 0; i--) {
        ifact[i] = mul(ifact[i + 1], i + 1);
    }
    cin >> t;
    while(t--) {
        cin >> n >> m;
        int ncr = mul(fact[n + m - 2], mul(ifact[n - 1], ifact[m - 1]));
        cout << mul(mul(ncr, 1 + (n > 1)), 1 + (m > 1)) << '\n';
    }
}
