#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, p, fact[200001], ifact[200001], ans[200001];

int mul(int x, int y) {
    return (1LL * x * y) % p;
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

void f(ll prod, int sum, int used, int cur, int lim) {
    if(prod > 1) {
        lim = min((ll) lim, (n + sum - used - 1) / (prod - 1));
    }
    for(int j = lim; j > 1; j--) {
        int taken = 0;
        ll pw = 1;
        while(true) {
            ++taken, pw *= j;
            if(used + taken + (prod * pw - sum - taken * j) > n) {
                break;
            }
            f(prod * pw, sum + taken * j, used + taken, mul(cur, ifact[taken]), j - 1);
        }
    }
    int num_ones = prod - sum;
    if(used + num_ones > 1 && used + num_ones <= n) {
        ans[used + num_ones] = (ans[used + num_ones] + mul(mul(fact[used + num_ones], ifact[num_ones]), cur)) % p;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> p;
    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    ifact[n] = exp(fact[n], p - 2);
    for(int i = n - 1; i >= 0; i--) {
        ifact[i] = mul(ifact[i + 1], i + 1);
    }
    f(1, 0, 0, 1, n);
    for(int i = 2; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << '\n';
}
