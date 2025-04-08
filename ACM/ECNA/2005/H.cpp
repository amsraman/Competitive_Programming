#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    int _ = 0;
    while(n > 0) {
        _++;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int i = n - 1; i >= 0; i--) {
            if(n % 2 == 1) {
                dp[i][i] = a[i];
            } else {
                dp[i][i] = -a[i];
            }
            for(int j = i + 1; j < n; j++) {
                if((j - i + 1) % 2 != n % 2) {
                    if(a[i] >= a[j]) {
                        dp[i][j] = dp[i + 1][j] - a[i];
                    } else {
                        dp[i][j] = dp[i][j - 1] - a[j];
                    }
                } else {
                    dp[i][j] = max(dp[i + 1][j] + a[i], dp[i][j - 1] + a[j]);
                }
            }
        }
        cout << "In game " << _ << ", the greedy strategy might lose by as many as " << dp[0][n - 1] << " points.\n";
        cin >> n;
    }
}