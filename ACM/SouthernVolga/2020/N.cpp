#include <bits/stdc++.h>

using namespace std;

int t, a[5], c[3];

int main() {
    cin >> t;
    while(t--) {
        cin >> c[0] >> c[1] >> c[2] >> a[0] >> a[1] >> a[2] >> a[3] >> a[4];
        c[0] -= a[0], c[1] -= a[1], c[2] -= a[2];
        int from3 = max(0, min(c[0], a[3])), from4 = max(0, min(c[1], a[4]));
        c[0] -= from3, a[3] -= from3, c[1] -= from4, a[4] -= from4;
        c[2] -= (a[3] + a[4]);
        cout << ((min({c[0], c[1], c[2]}) >= 0) ? "YES" : "NO") << endl;
    }
}