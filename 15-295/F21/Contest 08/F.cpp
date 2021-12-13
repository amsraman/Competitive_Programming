#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

int n, x[100000], y[100000];
ld pow2[100001], den, ans;

ld area_of_triangle(int i, int j, int k) {
    ld sd1 = (ld) x[i] * y[j] + (ld) x[j] * y[k] + (ld) x[k] * y[i];
    ld sd2 = (ld) y[i] * x[j] + (ld) y[j] * x[k] + (ld) y[k] * x[i];
    return abs(sd1 - sd2) / 2.0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    pow2[0] = 1.0;
    for(int i = 0; i < n; i++) {
        pow2[i + 1] = pow2[i] * 2.0;
        ans += (ld) y[(i + 1) % n] * x[i] - (ld) y[i] * x[(i + 1) % n];
    }
    ans = abs(ans) / 2.0, den = pow2[n] - 1 - n - (ld) n * (n - 1) / 2.0;
    for(int i = 0; i < n; i++) {
        ld area = 0;
        for(int j = 1; j <= min(n - 2, 60); j++) {
            int boundary_points = abs(__gcd(x[i] - x[(i + j) % n], y[i] - y[(i + j) % n]));
            ld wt = 1.0 / pow2[j + 1];
            if(n < 100) {
                wt = (pow2[n - j - 1] - 1.0) / den;
            }
            ans -= (area + boundary_points / 2.0) * wt;
            area += area_of_triangle(i, (i + j) % n, (i + j + 1) % n);
        }
    }
    cout << fixed << setprecision(9) << ans + 1 << '\n';
}