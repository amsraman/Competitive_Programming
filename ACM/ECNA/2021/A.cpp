#include <bits/stdc++.h>

using namespace std;

const int INF = 500;

int n, dp[100001], adds[4] = {1, 11};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    int cur = 1, num = 1;
    for(int i = 1; i <= n; i++) {
        dp[i] = INF;
    }
    while(cur <= n) {
        dp[cur] = num;
        cur = 10 * cur + 1, ++num;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 2; j++) {
            if(i > adds[j]) {
                dp[i] = min(dp[i], dp[i - adds[j]] + dp[adds[j]]);
            }
        }
        for(int j = 2; j * j <= i; j++) {
            if(i % j == 0) {
                dp[i] = min(dp[i], dp[j] + dp[i / j]);
            }
        }
        int cur = i / 10, p10 = 10;
        while(cur > 0) {
            if(i - cur * p10 >= p10 / 10) {
                dp[i] = min(dp[i], dp[cur] + dp[i - cur * p10]);
            }
            cur /= 10, p10 *= 10;
        }
    }
    cout << dp[n] << '\n';
}