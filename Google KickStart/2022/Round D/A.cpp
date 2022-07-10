#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        long double ans = 0;
        for(int i = 0; i < m - 1; i++) {
            ans += a[n - i - 1];
        }
        int sz = n - m + 1;
        if(sz & 1) {
            ans += a[sz / 2];
        } else {
            ans += (long double) (a[sz / 2 - 1] + a[sz / 2]) / 2.0;
        }
        cout << "Case #" << _ << ": " << fixed << setprecision(9) << ans << endl;
    }
}