#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ifstream cin("cheeseburger_corollary_2_input.txt");
    ofstream cout("output.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        ll a, b, c; cin >> a >> b >> c;
        auto decker_count = [&](ll x, ll y) {
            return max(0LL, min(2 * x + 2 * y - 1, x + 2 * y));
        };
        ll ans = max(decker_count((c % b) / a, c / b), decker_count(c / a, (c % a) / b));
        if(c >= a) ans = max(ans, decker_count(1, (c - a) / b));
        if(c >= 2 * a) ans = max(ans, decker_count(2, (c - 2 * a) / b));
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}