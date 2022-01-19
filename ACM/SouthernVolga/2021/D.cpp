#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int m, c[500000], frq[1000001], fact[500001], cur, ans1, ans2 = 1;

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> m;
    for(int i = 0; i < m; i++) {
        cin >> c[i];
        ++frq[c[i]];
        cur = (cur + c[i]) % mod;
    }
    fact[0] = 1;
    for(int i = 1; i <= m; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    for(int i = 1e6; i > 1; i--) {
        cur = (cur - mul(2, frq[i]) + mod) % mod;
        int spc = (cur + frq[i]) % mod;
        ans1 = (ans1 + mul(frq[i], mul(spc, i - 1))) % mod;
        ans2 = mul(ans2, mul(fact[frq[i]], fact[frq[i]]));
        frq[i - 2] += frq[i];
    }
    ans2 = mul(ans2, fact[frq[1]]);
    cout << ans1 << " " << ans2 << '\n';
}