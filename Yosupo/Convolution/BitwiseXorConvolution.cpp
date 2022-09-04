// 412 ms
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

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

void fwht(vector<int> & a, bool inv) {
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
        for(int i = 0; i < sz; i += 2 * len) {
            for(int j = i; j < i + len; j++) {
                int x = a[j], y = a[j + len];
                a[j] = (x + y) % mod;
                a[j + len] = (x - y + mod) % mod;
            }
        }
    }
    if(inv) {
        int inv_sz = exp(sz, mod - 2);
        for(int i = 0; i < sz; i++) {
            a[i] = (1LL * a[i] * inv_sz) % mod;
        }
    }
}

void fwht_conv(vector<int> & a, vector<int> & b) {
    int pow = 1, res_sz = a.size() + b.size() - 1;
    while(pow < res_sz) {
        pow <<= 1;
    }
    a.resize(pow), b.resize(pow);
    fwht(a, false), fwht(b, false);
    for(int i = 0; i < pow; i++) {
        a[i] = (1LL * a[i] * b[i]) % mod;
    }
    fwht(a, true);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(1 << n), b(1 << n);
    for(int i = 0; i < (1 << n); i++) {
        cin >> a[i];
    }
    for(int i = 0; i < (1 << n); i++) {
        cin >> b[i];
    }
    fwht_conv(a, b);
    for(int i = 0; i < (1 << n); i++) {
        cout << a[i] << " ";
    }
    cout << '\n';
}