#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int t, e, w, x[100][100];

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> e >> w;
        for(int i = 0; i < e; i++) {
            for(int j = 0; j < w; j++) {
                cin >> x[i][j];
            }
        }
        vector<vector<int>> common(e, vector<int>(e, 0));
        for(int i = 0; i < e; i++) {
            vector<int> mn_w(w, INF);
            for(int j = i; j < e; j++) {
                for(int k = 0; k < w; k++) {
                    mn_w[k] = min(mn_w[k], x[j][k]);
                    common[i][j] += mn_w[k];
                }
            }
        }
        vector<vector<int>> dp(e, vector<int>(e, 0));
        for(int i = e - 1; i >= 0; i--) {
            for(int j = i + 1; j < e; j++) {
                dp[i][j] = 0x3f3f3f3f;
                for(int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + 2 * common[i][k] + 2 * common[k + 1][j] - 4 * common[i][j]);
                }
            }
        }
        cout << "Case #" << _ << ": " << dp[0][e - 1] + 2 * common[0][e - 1] << endl;
    }
}