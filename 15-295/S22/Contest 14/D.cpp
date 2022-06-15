#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    vector<int> l(n), r(n);
    for(int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    ld ans = 0;
    for(int i = 0; i < n; i++) {
        int np1 = r[i] / p - (l[i] - 1) / p, np2 = r[(i + 1) % n] / p - (l[(i + 1) % n] - 1) / p;
        ld pb1 = (ld) np1 / (r[i] - l[i] + 1), pb2 = (ld) np2 / (r[(i + 1) % n] - l[(i + 1) % n] + 1);
        ans += 2000.0 * (1.0 - (1.0 - pb1) * (1.0 - pb2));
    }
    cout << fixed << setprecision(6) << ans << endl;
}