#include <bits/stdc++.h>

using namespace std;

int main() {
    int c, n; cin >> c >> n;
    vector<int> cd(n);
    for(int i = 0; i < n; i++) {
        cin >> cd[i];
    }
    vector<bitset<1001>> pdp(c + 1), dp(c + 1);
    pdp[0][0] = true;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= c; j++) {
            dp[j] = (pdp[j] | (pdp[j] << cd[i]));
            if(j >= cd[i]) {
                dp[j] = (dp[j] | pdp[j - cd[i]]);
            }
        }
        swap(dp, pdp);
    }
    int ans1 = 0, ans2 = 0;
    for(int i = 0; i <= c; i++) {
        for(int j = 0; j <= c; j++) {
            if(!pdp[i][j]) continue;
            if(i + j > ans1 + ans2) ans1 = i, ans2 = j;
            else if((i + j == ans1 + ans2) && abs(i - j) < abs(ans1 - ans2)) ans1 = i, ans2 = j;
        }
    }
    if(ans1 < ans2) swap(ans1, ans2);
    cout << ans1 << " " << ans2 << '\n';
}