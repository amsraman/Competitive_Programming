// 250 ms
#include <bits/stdc++.h>

using namespace std;

namespace NTT {
    const int mod = 998244353;

    int mul(int a, int b) {
        return (1LL * a * b) % mod;
    }
    
    int exp(int a, int b) {
        int ret = 1;
        while(b > 0) {
            if(b & 1) {
                ret = mul(ret, a);
            }
            a = mul(a, a), b >>= 1;
        }
        return ret;
    }

    void ntt(vector<int> & a, bool inv) {
        int sz = a.size();
        for(int i = 1, j = 0; i < sz; i++) {
            int bit = sz >> 1;
            for(; j & bit; bit >>= 1) {
                j ^= bit;
            }
            j ^= bit;
            if(i < j) {
                swap(a[i], a[j]);
            }
        }
        for(int len = 1; len < sz; len <<= 1) {
            int w = exp(3, mod / 2 / len);
            if(inv) {
                w = exp(w, mod - 2);
            }
            for(int i = 0; i < sz; i += (2 * len)) {
                int wn = 1;
                for(int j = i; j < i + len; j++) {
                    int x = a[j], y = mul(a[j + len], wn);
                    a[j] = (x + y) % mod;
                    a[j + len] = (x - y + mod) % mod;
                    wn = mul(wn, w);
                }
            }
        }
        if(inv) {
            int inv_n = exp(sz, mod - 2);
            for(int i = 0; i < sz; i++) {
                a[i] = mul(a[i], inv_n);
            }
        }
    }

    void ntt_conv(vector<int> & a, vector<int> & b) {
        int pow = 1, res_sz = a.size() + b.size() - 1;
        while(pow < res_sz) {
            pow <<= 1;
        }
        a.resize(pow), b.resize(pow);
        ntt(a, false), ntt(b, false);
        for(int i = 0; i < pow; i++) {
            a[i] = mul(a[i], b[i]);
        }
        ntt(a, true);
    }
}

using namespace NTT;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v1(n + 1), v2(n + 1), fact(n + 1), ifact(n + 1);
    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    ifact[n] = exp(fact[n], mod - 2);
    for(int i = n - 1; i >= 0; i--) {
        ifact[i] = mul(ifact[i + 1], i + 1);
    }
    for(int i = 0; i <= n; i++) {
        v1[i] = mul(i & 1 ? NTT::mod - 1 : 1, ifact[i]);
        v2[i] = mul(exp(i, n), ifact[i]);
    }
    NTT::ntt_conv(v1, v2);
    for(int i = 0; i <= n; i++) {
        cout << v1[i] << " ";
    }
    cout << '\n';
}