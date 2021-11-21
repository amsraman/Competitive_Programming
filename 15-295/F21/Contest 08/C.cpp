#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int n, m, a[100000], b[100000], ans;

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
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int cur = 1, denom = exp(m, mod - 2), i2 = exp(2, mod - 2);
    for(int i = 0; i < n; i++) {
        if(a[i] == 0 && b[i] == 0) {
            // (1 - 1 / m) / 2
            int diff = (1 - denom + mod) % mod;
            ans = (ans + mul(cur, mul(diff, i2))) % mod;
            cur = mul(cur, denom);
        } else if(b[i] == 0) {
            ans = (ans + mul(cur, mul(a[i] - 1, denom))) % mod;
            cur = mul(cur, denom);
        } else if(a[i] == 0) {
            ans = (ans + mul(cur, mul(m - b[i], denom))) % mod;
            cur = mul(cur, denom);
        } else if(a[i] != b[i]) {
            if(a[i] > b[i]) {
                ans = (ans + cur) % mod;
            }
            break;
        }
    }
    cout << ans << endl;
}