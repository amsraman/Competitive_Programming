#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 998244353;

int m, k, num[1000001];

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
    cin >> m >> k;
    for(int i = k; i > 0; i--) {
        num[i] = (exp(2 * (k / i) + 1, m) + mod - 1) % mod;
        for(int j = 2 * i; j <= k; j += i) {
            num[i] = (num[i] - num[j] + mod) % mod;
        }
    }
    cout << (num[1] + 1) % mod << endl;
}