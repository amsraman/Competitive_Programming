#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int n, q, c[100], b[100], x, lb[101], ps_lb[102], dp[101][100001], ans;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for(int i = 0; i < n - 1; i++) {
        cin >> b[i];
    }
    cin >> q >> x;
    lb[0] = ps_lb[1] = x;
    for(int i = 1; i < n; i++) {
        lb[i] = lb[i - 1] + b[i - 1];
        ps_lb[i + 1] = ps_lb[i] + lb[i];
    }
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int sum = 0; sum <= 1e4; sum++) {
            for(int cur = 0; cur <= c[i - 1]; cur++) {
                if(sum + cur <= 1e4 && cur >= lb[i - 1] - sum + ps_lb[i - 1]) {
                    dp[i][sum + cur] = (dp[i][sum + cur] + dp[i - 1][sum]) % mod;
                }
            }
            if(i == n) {
                ans = (ans + dp[i][sum]) % mod;
            }
        }
    }
    cout << ans << endl;
}