#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

int n, a[200000];

ld f(ld x) {
    vector<ld> dp1(n), dp2(n);
    for(int i = 0; i < n; i++) {
        dp1[i] = dp2[i] = a[i] - x;
    }
    ld mn = 0, mx = 0;
    for(int i = 0; i < n; i++) {
        if(i > 0) {
            dp1[i] += min((ld) 0.0, dp1[i - 1]);
            dp2[i] += max((ld) 0.0, dp2[i - 1]);
        }
        mn = min(mn, dp1[i]);
        mx = max(mx, dp2[i]);
    }
    return max(abs(mn), abs(mx));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ld lb = -5e5, ub = 5e5;
    for(int i = 0; i < 100; i++) {
        ld m1 = lb + (ub - lb) / 3.0, m2 = ub - (ub - lb) / 3.0;
        if(f(m1) < f(m2)) {
            ub = m2;
        } else {
            lb = m1;
        }
    }
    cout << fixed << setprecision(9) << f(ub) << '\n';
}