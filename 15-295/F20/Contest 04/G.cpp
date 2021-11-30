#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 0xffffffffff;

int n, k;
ll a[50], pos[52], dp[52][52][51];

bool in_bound(ll l, ll r, ll x) {
    return (x >= l && x <= r);
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        pos[i] = a[i];
    }
    cin >> k;
    pos[n] = INF, pos[n + 1] = -INF;
    sort(pos, pos + n + 2);
    for(int i = n + 1; i >= 0; i--) {
        for(int j = i; j <= n + 1; j++) {
            for(int pl = 0; pl < n - 1; pl++) {
                if(in_bound(pos[i], pos[j], a[pl]) && in_bound(pos[i], pos[j], a[pl + 1])) {
                    dp[i][j][0] += min(abs(a[pl + 1] - a[pl]), min(abs(pos[j] - a[pl]), abs(pos[i] - a[pl])) + min(abs(pos[j] - a[pl + 1]), abs(pos[i] - a[pl + 1])));
                } else if(in_bound(pos[i], pos[j], a[pl])) {
                    dp[i][j][0] += min(abs(pos[i] - a[pl]), abs(pos[j] - a[pl]));
                } else if(in_bound(pos[i], pos[j], a[pl + 1])) {
                    dp[i][j][0] += min(abs(pos[i] - a[pl + 1]), abs(pos[j] - a[pl + 1]));
                }
            }
            for(int t = 1; t <= k; t++) {
                dp[i][j][t] = INF;
                for(int s = i; s <= j; s++) {
                    dp[i][j][t] = min(dp[i][j][t], dp[i][s][0] + dp[s][j][t - 1]);
                }
            }
        }
    }
    cout << dp[0][n + 1][k] << endl;
}