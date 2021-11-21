#include <bits/stdc++.h>

using namespace std;

int n, k, a[100000], sufmin[100001];

int main() {
    cin >> n >> k;
    int mx = -1e9, mn = 1e9;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
        mn = min(mn, a[i]);
    }
    if(k >= 3) {
        cout << mx << endl;
    } else if(k == 2) {
        int mn1 = a[0], ans = mn;
        sufmin[n - 1] = a[n - 1];
        for(int i = n - 2; i >= 0; i--) {
            sufmin[i] = min(a[i], sufmin[i + 1]);
        }
        for(int i = 1; i < n; i++) {
            ans = max(ans, max(mn1, sufmin[i]));
            mn1 = min(mn1, a[i]);
        }
        cout << ans << endl;
    } else {
        cout << mn << endl;
    }
}