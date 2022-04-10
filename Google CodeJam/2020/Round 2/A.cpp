#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll l, r;

ll mx_ar(ll x, ll s, ll d) {
    __int128_t lb = 0, ub = 1e10;
    while(lb < ub) {
        __int128_t mid = (lb + ub + 1) / 2, sum = mid * (2 * s + (mid - 1) * d) / 2;
        if(sum > x) {
            ub = mid - 1;
        } else {
            lb = mid;
        }
    }
    return ub;
}

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> l >> r;
        bool sw = false;
        if(l < r) {
            swap(l, r);
            sw = true;
        }
        ll df = l - r, ans = mx_ar(df, 1, 1);
        l -= ans * (ans + 1) / 2;
        if(sw && l == r) {
            sw = false;
        }
        ll m1 = mx_ar(l, ans + 1, 2), m2 = mx_ar(r, ans + 2, 2);
        if(m1 < m2 || m1 == m2 + 1) {
            l -= m1 * (2 * (ans + 1) + (m1 - 1) * 2) / 2;
            r -= (m1 - 1) * (2 * (ans + 2) + (m1 - 2) * 2) / 2;
            ans += 2 * m1 - 1;
        } else {
            l -= m2 * (2 * (ans + 1) + (m2 - 1) * 2) / 2;
            r -= m2 * (2 * (ans + 2) + (m2 - 1) * 2) / 2;
            ans += 2 * m2;
        }
        if(sw) {
            swap(l, r);
        }
        cout << "Case #" << _ << ": " << ans << " " << l << " " << r << endl;
    }
}