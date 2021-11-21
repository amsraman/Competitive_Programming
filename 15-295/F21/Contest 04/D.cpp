#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, a[100], dp[10001][101], ans;
map<int, int> num;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ++num[a[i]];
    }
    dp[0][0] = 1;
    for(auto it: num) {
        int i = it.f;
        for(int j = 10000; j >= 0; j--) {
            if(j >= i) {
                for(int k = 1; k <= n; k++) {
                    for(int l = 1; l <= min(k, it.s); l++) {
                        if(j >= l * i) {
                            dp[j][k] = min(2, dp[j][k] + dp[j - l * i][k - l]);
                        }
                    }
                }
            }
        }
    }
    int tot = 0;
    for(auto it: num) {
        for(int i = 1; i <= it.s; i++) {
            if(dp[it.f * i][i] == 1) {
                ans = max(ans, i);
            }
        }
        ++tot;
    }
    if(tot <= 2) {
        ans = n;
    }
    cout << ans << endl;
}