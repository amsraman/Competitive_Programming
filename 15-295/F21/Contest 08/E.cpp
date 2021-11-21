#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int n, fact[1000001], ifact[1000001], pow3[1000001], npow3[1000001], one, two;

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int exp(int x, long long y) {
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
    return mul(fact[x], mul(ifact[x - y], ifact[y]));
}

int main() {
    cin >> n;
    int pw3 = exp(3, n);
    fact[0] = pow3[0] = npow3[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i);
        pow3[i] = mul(pow3[i - 1], 3);
        npow3[i] = mul(npow3[i - 1], pw3);
    }
    ifact[n] = exp(fact[n], mod - 2);
    for(int i = n - 1; i >= 0; i--) {
        ifact[i] = mul(ifact[i + 1], i + 1);
    }
    for(int i = 1; i <= n; i++) {
        if(i % 2 == 1) {
            one = (one + mul(ncr(n, i), mul(pow3[i], npow3[n - i]))) % mod;
        } else {
            one = (one - mul(ncr(n, i), mul(pow3[i], npow3[n - i])) + mod) % mod;
        }
    }
    for(int i = 0; i < n; i++) {
        int neg = mod - pow3[i];
        int sum = (exp(1 + neg, n) - exp(neg, n) + mod) % mod;
        if(i % 2 == 1) {
            two = (two - mul(ncr(n, i), sum) + mod) % mod;
        } else {
            two = (two + mul(ncr(n, i), sum)) % mod;
        }
    }
    cout << (mul(2, one) - mul(3, two) + mod) % mod << endl;
}