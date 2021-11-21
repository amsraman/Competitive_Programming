#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

int n, a[100000], ct[1000001], ans = 1;

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
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        int tmp = a[i];
        for(int j = 2; j * j <= tmp; j++) {
            if(tmp % j == 0) {
                int cnt = 0;
                while(tmp % j == 0) {
                    ++cnt, tmp /= j;
                }
                ct[j] += cnt % 2;
            }
        }
        if(tmp > 1) {
            ct[tmp]++;
        }
    }
    for(int i = 2; i <= 1000000; i++) {
        ans = mul(ans, exp(i, min(ct[i], n - ct[i])));
    }
    cout << ans << '\n';
}