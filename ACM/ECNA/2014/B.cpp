#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> len(501);
    for(int i = 0; i <= 500; i++) {
        len[i] = to_string(i).length();
    }
    string s; cin >> s;
    for(int _ = 1; s != "0"; _++) {
        int n = s.length();
        vector<vector<vector<bool>>> prd(n, vector<vector<bool>>(n, vector<bool>(n, false)));
        vector<vector<int>> dp(n, vector<int>(n, 1e5));
        for(int i = 0; i < n; i++) {
            for(int len = 1; len <= n; len++) {
                prd[i][i][len] = true;
                for(int j = i + 1; j < n; j++) {
                    prd[i][j][len] = prd[i][j - 1][len];
                    if(j >= i + len && s[j] != s[j - len]) prd[i][j][len] = false;
                }
            }
        }
        for(int i = n - 1; i >= 0; i--) {
            dp[i][i] = 1;
            for(int j = i + 1; j < n; j++) {
                dp[i][j] = j - i + 1;
                for(int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
                int cur_len = j - i + 1;
                for(int k = 1; k <= cur_len; k++) {
                    if(cur_len % k == 0 && prd[i][j][k]) {
                        dp[i][j] = min(dp[i][j], dp[i][i + k - 1] + len[cur_len / k] + (k == 1 ? 0 : 2));
                    }
                }
            }
        }
        cout << "Case " << _ << ": " << dp[0][n - 1] << '\n';
        cin >> s;
    }
}