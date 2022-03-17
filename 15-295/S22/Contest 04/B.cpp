#include <bits/stdc++.h>

using namespace std;

int n, x[100000], h[100000], dp[100000][3];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> h[i];
    }
    dp[0][0] = dp[0][2] = 1;
    for(int i = 1; i < n; i++) {
        if(x[i] - h[i] > x[i - 1]) {
            dp[i][0] = max(dp[i - 1][0] + 1, dp[i - 1][1] + 1);
        }
        if(x[i] - h[i] > x[i - 1] + h[i - 1]) {
            dp[i][0] = max(dp[i][0], dp[i - 1][2] + 1);
        }
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]);
        dp[i][2] = max(dp[i - 1][0] + 1, dp[i - 1][1] + 1);
        if(x[i - 1] + h[i - 1] < x[i]) {
            dp[i][1] = max(dp[i][1], dp[i - 1][2]);
            dp[i][2] = max(dp[i][2], dp[i - 1][2] + 1);
        }
    }
    cout << max({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]}) << endl;
}