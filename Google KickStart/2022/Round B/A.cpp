#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const long double PI = 4.0 * atanl(1.0);

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int r, a, b;
        cin >> r >> a >> b;
        ll rad1 = 1LL * a * r, rad2 = 1LL * r * a / b, ans = 1LL * r * r + 1LL * rad1 * rad1 + 1LL * rad2 * rad2;
        while(rad2 > 0) {
            rad1 = rad2 * a;
            rad2 = rad1 / b;
            ans += 1LL * rad1 * rad1 + 1LL * rad2 * rad2;
        }
        cout << "Case #" << _ << ": " << fixed << setprecision(6) << PI * ans << endl;
    }
}