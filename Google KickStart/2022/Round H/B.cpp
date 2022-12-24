#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    vector<int> dp(1e5 + 2, 0x3f3f3f3f);
    dp[1] = 1;
    for(int i = 1; i <= 1e5; i++) {
        dp[i + 1] = min(dp[i + 1], dp[i] + 1);
        for(int j = 2 * i; j <= 1e5; j += i) {
            dp[j] = min(dp[j], dp[i] + 4 + 2 * (j / i - 1));
        }
    }
    for(int _ = 1; _ <= t; _++) {
        int l;
        cin >> l;
        cout << "Case #" << _ << ": " << dp[l] << endl;
    }
}
// dp[i] is the min cost to toss out i lillies
// dp[i] = min_{j | i} dp[j] + 4 + 2 * i / j;