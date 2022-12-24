#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> monst(n), spec(m), ps(2e5 + 1, 0), up(n + 1), down(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> monst[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> spec[i];
        ps[spec[i]] = 1;
    }
    for(int i = 1; i <= 2e5; i++) {
        ps[i] += ps[i - 1];
    }
    sort(monst.begin(), monst.end()); sort(spec.begin(), spec.end());
    for(int i = n - 1; i >= 0; i--) {
        if(i < n - 1 && monst[i + 1] == monst[i] + 1) {
            up[i + 1] = up[i + 2];
        } else {
            up[i + 1] = i + 1;
        }
    }
    for(int i = 0; i < n; i++) {
        if(i > 0 && monst[i - 1] + 1 == monst[i]) {
            down[i + 1] = down[i];
        } else {
            down[i + 1] = i;
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>(2, 0)); // 0: end doesn't move; 1: nonrestrictive
    for(int i = 0; i < n; i++) {
        dp[i + 1][0] = dp[i][1], dp[i + 1][1] = max(dp[i + 1][1], dp[i][1]);
        if(i < n - 1 && monst[i + 1] == monst[i] + 1) { // can't break apart streaks in the beginning
            continue;
        }
        for(int j = 0; j < m; j++) { // case on the first thing that is included in this streak
            if(spec[j] <= monst[i] && i - monst[i] + spec[j] >= 0) {
                dp[i + 1][0] = max(dp[i + 1][0], dp[down[i - monst[i] + spec[j] + 1]][1] + ps[monst[i]] - ps[spec[j] - 1]);
            }
        }
        dp[i + 1][1] = max(dp[i + 1][1], dp[i + 1][0]);
        for(int j = 0; j < m; j++) { // case on the last thing that is included in this streak
            if(spec[j] >= monst[i] && i + spec[j] - monst[i] < n) {
                dp[up[i + spec[j] - monst[i] + 1]][1] = max(dp[up[i + spec[j] - monst[i] + 1]][1], dp[i + 1][0] + ps[spec[j]] - ps[monst[i]]);
            }
        }
    }
    cout << dp[n][1] << '\n';
}
