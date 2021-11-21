#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, m, k, p[5000];
ll ps[5001], dp[5000][5001], ans;

int main() {
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        ps[i + 1] = ps[i] + p[i];
    }
    for(int i = 1; i <= k; i++) {
        ll cur = 0;
        for(int j = 0; j < n; j++) {
            if(j >= m - 1) {
                dp[j][i] = cur + ps[j + 1] - ps[j - m + 1];
                cur = max(cur, dp[j - m + 1][i - 1]);
            }
            if(i == k) {
                ans = max(ans, dp[j][i]);
            }
        }
    }
    cout << ans << endl;
}