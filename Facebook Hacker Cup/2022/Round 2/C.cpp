#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7, max_fact = 9000000;

int fact[max_fact + 1], ifact[max_fact + 1];

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

int ncr(int x, int y) {
    if(x < y) {
        return 0;
    }
    return mul(fact[x], mul(ifact[y], ifact[x - y]));
}

int main() {
    ifstream cin("balance_scale_input.txt");
    ofstream cout("output.txt");
    fact[0] = 1;
    for(int i = 1; i <= max_fact; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    ifact[max_fact] = exp(fact[max_fact], mod - 2);
    for(int i = max_fact - 1; i >= 0; i--) {
        ifact[i] = mul(ifact[i + 1], i + 1);
    }
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, k, tot = 0, lower = 0, opps = 0;
        cin >> n >> k;
        ++k;
        vector<int> c(n), w(n);
        for(int i = 0; i < n; i++) {
            cin >> c[i] >> w[i];
            tot += c[i];
            if(i > 0) {
                if(w[i] < w[0]) {
                    lower += c[i];
                } else if(w[i] == w[0]) {
                    opps += c[i];
                }
            }
        }
        int ans = (ncr(lower + opps + c[0], k) - ncr(lower, k) + mod) % mod;
        ans = mul(ans, mul(c[0], mul(fact[c[0] + opps - 1], ifact[c[0] + opps])));
        cout << "Case #" << _ << ": " << mul(ans, exp(ncr(tot, k), mod - 2)) << endl;
    }
}