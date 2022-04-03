#include <bits/stdc++.h>

using namespace std;

int t, c[3], m[3], y[3], k[3];

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        for(int i = 0; i < 3; i++) {
            cin >> c[i] >> m[i] >> y[i] >> k[i];
        }
        c[2] = min({c[0], c[1], c[2]});
        m[2] = min({m[0], m[1], m[2]});
        y[2] = min({y[0], y[1], y[2]});
        k[2] = min({k[0], k[1], k[2]});
        int tot = c[2] + m[2] + y[2] + k[2];
        cout << "Case #" << _ << ": ";
        if(tot < 1e6) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            int extra = c[2] + m[2] + y[2] + k[2] - 1e6, mn;
            mn = min(extra, c[2]), extra -= mn, c[2] -= mn;
            mn = min(extra, m[2]), extra -= mn, m[2] -= mn;
            mn = min(extra, y[2]), extra -= mn, y[2] -= mn;
            mn = min(extra, k[2]), extra -= mn, k[2] -= mn;
            cout << c[2] << " " << m[2] << " " << y[2] << " " << k[2] << endl;
        }
    }
}