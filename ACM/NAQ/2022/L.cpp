#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int t, s; cin >> t >> s;
    ll num = 0, den = 0;
    for(int i = 1; i <= s; i++) {
        // two lines: y = 2s-2x, y = s - x/2
        ll lim = min((2 * s - i) / 2, 2 * s - 2 * i);
        den += 2 * lim + 1;
        if(i <= t) num += 2 * min(lim, 1LL * t - i) + 1;
    }
    num *= 2, den *= 2;
    num += 2 * min(s, t) + 1;
    den += 2 * s + 1;
    ll g = __gcd(num, den);
    num /= g, den /= g;
    if(den == 1) {
        cout << num << '\n';
    } else {
        cout << num << '/' << den << '\n';
    }
}