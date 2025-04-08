#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

const ld PI = 3.141592653589793238462643383279502884197;
const ld eps = 1e-9;

ld ldabs(ld x) {
    return x < 0 ? -x : x;
}

int main() {
    ld r, s, h; cin >> r >> s >> h;
    ld total_hours = 2.0 * PI * r / s;
    ld total_days = total_hours / h;
    int ans1, ans2, ans3;
    ld best = 1e50;
    for(int i = 2; i <= 1000; i++) {
        for(int j = 2 * i; j <= 1000; j += i) {
            for(int k = 2 * j; k <= 1000; k += j) {
                // k years total
                int num_leap = k / i - k / j + 1;
                ld app_days;
                if(total_days - floor(total_days) > 0.5 - eps) {
                    app_days = (ceil(total_days) * k - num_leap) / k;
                } else {
                    app_days = (floor(total_days) * k + num_leap) / k;
                }
                if(ldabs(total_days - app_days) < best) {
                    best = ldabs(total_days - app_days);
                    ans1 = i, ans2 = j, ans3 = k;
                }
            }
        }
    }
    cout << ans1 << " " << ans2 << " " << ans3 << '\n';
    return 0;
}