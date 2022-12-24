#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n), ct(1e6 + 1), dp(1e6 + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ++ct[a[i]], ++dp[a[i]];
    }
    int ans = 0;
    for(int i = 1; i <= 1e6; i++) {
        ans = max(ans, dp[i]);
        for(int j = 2 * i; j <= 1e6; j += i) {
            if(ct[j] > 0) {
                dp[j] = max(dp[j], dp[i] + ct[j]);
            }
        }
    }
    cout << ans << endl;
}