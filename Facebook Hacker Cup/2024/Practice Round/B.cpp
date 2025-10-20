#include <bits/stdc++.h>

using namespace std;

using fl = long double;

int main() {
    ifstream cin("line_by_line_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, p; cin >> n >> p;
        fl prb = (fl) p / 100;
        auto exp_less = [&](fl x, fl targ) {
            fl cur = 1;
            for(int i = 0; i < n; i++) {
                cur *= x;
                if(x > 1 && cur > targ) return false;
                if(x < 1 && cur < targ) return true;
            }
            return cur <= targ;
        };
        fl lb = 0, ub = 1;
        for(int it = 0; it < 100; it++) {
            fl mid = (lb + ub) / 2;
            if(exp_less(mid, prb)) {
                lb = mid;
            } else {
                ub = mid;
            }
        }
        fl ans = prb / ub - prb; ans *= 100;
        cout << "Case #" << _ << ": " << fixed << setprecision(9) << ans << '\n';
    }
}
/*
n * p^(n - 1) * (1 - p) + p^n

(p^(n - 1) * (n + p * (1 - p)))^(1/n) - p


p^((n - 1) / n) * (p + n * (1 - p)) ^ (1 / n)
*/