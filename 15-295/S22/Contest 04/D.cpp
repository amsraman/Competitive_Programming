#include <bits/stdc++.h>

using namespace std;

int n, a[100000], pv[201], cmp[201], inc[201][201], ans;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i <= 200; i++) {
        for(int j = 0; j <= 200; j++) {
            inc[i][j] = -3e5;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= 200; j++) {
            pv[j] = cmp[j];
        }
        for(int j = a[i]; j <= 200; j++) {
            cmp[j] = max(cmp[j], inc[j][j - a[i]] + 1);
        }
        for(int j = a[i]; j <= 200; j++) {
            inc[j][a[i]] = max(inc[j][a[i]], pv[j] + 1);
        }
    }
    for(int i = 0; i <= 200; i++) {
        ans = max(ans, cmp[i]);
    }
    cout << ans << '\n';
}