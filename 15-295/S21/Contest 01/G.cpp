#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 998244353;

int n, k, fact[10000001], ifact[10000001], dp[10000001];

int mul(int a, int b) {
    return ((ll) a * b) % mod;
}

int exp(int a, int b) {
    int ret = 1;
    while(b) {
        if(b & 1) {
            ret = mul(ret, a);
        }
        a = mul(a, a), b >>= 1;
    }
    return ret;
}

int main() {
    cin >> n >> k;
    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    ifact[n] = exp(fact[n], mod - 2);
    for(int i = n - 1; i >= 0; i--) {
        ifact[i] = mul(ifact[i + 1], i + 1);
    }
    dp[0] = 1;
    for(int i = 1, tot = 1; i <= n; i++) {
        dp[i] = mul(tot, mul(ifact[i], fact[i - 1]));
        if(i >= k) {
            tot = (tot - dp[i - k] + mod) % mod;
        }
        tot = (tot + dp[i]) % mod;
    }
    cout << mul(fact[n], dp[n]) << endl;
}