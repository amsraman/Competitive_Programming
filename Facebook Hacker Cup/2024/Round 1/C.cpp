#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 998244353;

int main() {
    ifstream cin("substantial_losses_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        ll w, g, l; cin >> w >> g >> l;
        int df = (w - g) % mod;
        int one = (2 * l + 1) % mod;
        int ans = (1LL * df * one) % mod;
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}
/*

I'm currently at position i. what's the expected amount of time for me to go back

at any point, with 1/2 probability, I will spend f(i + 1) + 1 for no reason
with 1/2 probability i'm done

let x = f(i + 1) + 1

1/2 * 1 + 1/4 * (1 + x) + 1/8 * (1 + 2x) + 1/16 * (1 + 3x) + ...

1/2 + 1/4 + 1/8 + ... = 1
+
1/4 * x + 1/8 * 2x + 1/16 * 3x + ...

lower part = 

1/2 * (1/2 * x + 1/4 * 2x + 1/8 * 3x + ...) = x

x + 1

f(i + 1) + 2

1 + 2L * (W - G)
*/