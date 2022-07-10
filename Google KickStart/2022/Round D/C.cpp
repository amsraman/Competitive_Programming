#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m;
        cin >> n;
        vector<int> s(n);
        for(int i = 0; i < n; i++) {
            cin >> s[i];
            --s[i];
        }
        cin >> m;
        vector<int> k(m);
        for(int i = 0; i < m; i++) {
            cin >> k[i];
            --k[i];
        }
        vector<vector<int>> ln(m, vector<int>(2500, -1)), rn(m, vector<int>(2500, m));
        for(int i = 1; i < m; i++) {
            for(int j = 0; j < 2500; j++) {
                ln[i][j] = ln[i - 1][j];
            }
            ln[i][k[i - 1]] = i - 1;
        }
        for(int i = m - 2; i >= 0; i--) {
            for(int j = 0; j < 2500; j++) {
                rn[i][j] = rn[i + 1][j];
            }
            rn[i][k[i + 1]] = i + 1;
        }
        vector<vector<int>> dp(n, vector<int>(m, INF));
        for(int i = 0; i < m; i++) {
            if(k[i] == s[0]) {
                dp[0][i] = 0;
            }
        }
        for(int i = 0; i < n - 1; i++) {
            int nxt = s[i + 1];
            for(int j = 0; j < m; j++) {
                if(k[j] == nxt) {
                    dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
                }
                if(ln[j][nxt] != -1) {
                    dp[i + 1][ln[j][nxt]] = min(dp[i + 1][ln[j][nxt]], dp[i][j] + abs(j - ln[j][nxt]));
                }
                if(rn[j][nxt] != m) {
                    dp[i + 1][rn[j][nxt]] = min(dp[i + 1][rn[j][nxt]], dp[i][j] + abs(j - rn[j][nxt]));
                }
            }
        }
        int ans = INF;
        for(int i = 0; i < m; i++) {
            ans = min(ans, dp[n - 1][i]);
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}