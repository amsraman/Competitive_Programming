#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, d;
        cin >> n >> d;
        vector<int> v(n);
        for(int i = 0; i < n; i++) {
            cin >> v[i];
        }
        auto df = [&](int x, int y) {
            return min((y - x + d) % d, (x - y + d) % d);
        };
        vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(2, 0)));
        for(int i = n - 1; i >= 0; i--) {
            for(int j = i + 1; j < n; j++) {
                dp[i][j][0] = min(df(v[i], v[j]) + dp[i + 1][j][1], df(v[i], v[i + 1]) + dp[i + 1][j][0]);
                dp[i][j][1] = min(df(v[i], v[j]) + dp[i][j - 1][0], df(v[j], v[j - 1]) + dp[i][j - 1][1]);
            }
        }
        ll ans = min(df(v[0], 0) + dp[0][n - 1][0], df(v[n - 1], 0) + dp[0][n - 1][1]);
        cout << "Case #" << _ << ": " << ans << endl;
    }
}