#include <bits/stdc++.h>

using namespace std;

int n, a[300], dp[300][300];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for(int j = i + 1; j < n; j++) {
            dp[i][j] = n + 1;
            for(int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
            if(a[i] == a[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 1;
                for(int k = i; k <= j; k++) {
                    if(a[k] == a[i]) {
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] - 1);
                    }
                }
            }
        }
    }
    cout << dp[0][n - 1] << endl;
}