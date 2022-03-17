#include <bits/stdc++.h>

using namespace std;

int n, b, a[100], dp[100][101], ans;

int main() {
    cin >> n >> b;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        int o = 0, e = 0;
        for(int j = i - 1; j >= 0; j--) {
            o += (a[j + 1] % 2);
            e += 1 - (a[j + 1] % 2);
            if(o == e) {
                int cst = abs(a[j] - a[j + 1]);
                for(int k = 0; k + cst <= b; k++) {
                    dp[i][k + cst] = max(dp[i][k + cst], dp[j][k] + 1);
                }
            }
        }
    }
    for(int i = 0; i <= b; i++) {
        ans = max(ans, dp[n - 1][i]);
    }
    cout << ans << endl;
}