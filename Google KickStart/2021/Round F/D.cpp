#include <bits/stdc++.h>
typedef long long ll;
#define int long long

using namespace std;

int t, n, m, k, adj[15][15], l[15], r[15], a[15], dp[(1 << 15)][15];
// dp[msk][i] = number of ways to go through the subset msk, ending at i

ll subset_sum(int msk) {
    ll ret = 0;
    for(int i = 0; i < n; i++) {
        if((1 << i) & msk) {
            ret += a[i];
        }
    }
    return ret;
}

bool reachable(int msk, int v) {
    for(int i = 0; i < n; i++) {
        if(((1 << i) & msk) && adj[i][v] == 1) {
            return true;
        }
    }
    return false;
}

signed main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> m >> k;
        for(int i = 0; i < n; i++) {
            cin >> l[i] >> r[i] >> a[i];
        }
        memset(adj, 0, sizeof(adj));
        for(int i = 0, x, y; i < m; i++) {
            cin >> x >> y;
            adj[x][y] = adj[y][x] = 1;
        }
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < n; i++) {
            dp[(1 << i)][i] = 1;
        }
        for(int i = 0; i < (1 << n); i++) {
            for(int j = 0; j < n; j++) {
                if((1 << j) & i) {
                    for(int lst = 0; lst < n; lst++) {
                        if(((1 << lst) & i) && (lst != j)) {
                            int pv_msk = (i ^ (1 << j));
                            ll pv_sum = subset_sum(pv_msk);
                            if(pv_sum >= l[j] && pv_sum <= r[j] && reachable(pv_msk, j)) {
                                dp[i][j] += dp[pv_msk][lst];
                            }
                        }
                    }
                }
            }
        }
        ll ans = 0;
        for(int i = 0; i < (1 << n); i++) {
            if(subset_sum(i) == k) {
                for(int j = 0; j < n; j++) {
                    ans += dp[i][j];
                }
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}