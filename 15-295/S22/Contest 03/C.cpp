#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;

using namespace std;

const ld eps = 1e-9;

int n, sgn = 1, x[100000], y[100000];

bool ok(ld rad) {
    ld mn = 1e18, mx = -1e18;
    for(int i = 0; i < n; i++) {
        ld sd1 = abs(rad * sgn - y[i]);
        if(sd1 > rad) {
            return false;
        }
        ld sd2 = sqrt((rad - sd1) * (rad + sd1));
        mn = min(mn, x[i] + sd2), mx = max(mx, x[i] - sd2);
    }
    return (mx <= mn);
}

int main() {
    cin >> n;
    int num_neg = 0, num_pos = 0, num_zer = 0;
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        num_neg += (y[i] < 0);
        num_pos += (y[i] > 0);
        num_zer += (y[i] == 0);
    }
    if((num_neg != 0 && num_pos != 0) || num_zer > 1) {
        cout << -1 << endl;
    } else {
        for(int i = 0; i < n; i++) {
            if(y[i] < 0) {
                sgn = -1;
            }
        }
        ld lb = 0, ub = 1e14;
        for(int i = 0; i < 100; i++) {
            ld mid = lb + (ub - lb) / 2.0;
            if(ok(mid)) {
                ub = mid;
            } else {
                lb = mid;
            }
        }
        cout << fixed << setprecision(9) << ub << endl;
    }
}