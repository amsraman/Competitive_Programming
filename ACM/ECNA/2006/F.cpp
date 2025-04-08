#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

const ld eps = 1e-9;

int main() {
    int n, k; cin >> n >> k;
    while(n > 0) {
        vector<pair<ld, ld>> pts;
        for(int i = 0; i < n; i++) {
            ld x, y; cin >> x >> y;
            pts.emplace_back(x, y);
        }
        sort(pts.begin(), pts.end());
        auto turn = [](pair<ld, ld> x, pair<ld, ld> y, pair<ld, ld> z) {
            ld dx1 = y.first - x.first, dx2 = z.first - y.first, dy1 = y.second - x.second, dy2 = z.second - y.second;
            if(dx1 * dy2 - dx2 * dy1 > eps) {
                return 1;
            } else if(dx2 * dy1 - dx1 * dy2 > eps) {
                return -1;
            }
            return 0;
        };
        vector<int> hull(n), lst(n, -1); int tp = 0;
        for(int i = 0; i < n; i++) {
            while(tp > 1 && turn(pts[hull[tp - 2]], pts[hull[tp - 1]], pts[i]) != -1) {
                lst[hull[--tp]] = -1;
            }
            if(tp > 0) lst[i] = hull[tp - 1];
            hull[tp++] = i;
        }
        vector<vector<ld>> dp(n, vector<ld>(k, 1e18));
        ld ans = 1e18;
        for(int i = 0; i < n; i++) {
            if(lst[i] == -1) continue;
            ld m = (pts[i].second - pts[lst[i]].second) / (pts[i].first - pts[lst[i]].first), b = pts[i].second - m * pts[i].first;
            dp[i][0] = 0;
            for(int j = 0; j < i; j++) {
                auto [x, y] = pts[j];
                dp[i][0] = max(dp[i][0], m * x + b - y);
            }
            for(int j = 1; j < k; j++) {
                for(int pv = 0; pv < i; pv++) {
                    if(lst[pv] == -1) continue;
                    ld pm = (pts[pv].second - pts[lst[pv]].second) / (pts[pv].first - pts[lst[pv]].first), pb = pts[pv].second - pm * pts[pv].first;
                    ld cur = dp[pv][j - 1];
                    for(int btw = pv; btw <= i; btw++) {
                        auto [x, y] = pts[btw];
                        cur = max(cur, min(pm * x + pb - y, m * x + b - y));
                    }
                    dp[i][j] = min(dp[i][j], cur);
                }
            }
            ld res = dp[i][k - 1];
            for(int j = i + 1; j < n; j++) {
                auto [x, y] = pts[j];
                res = max(res, m * x + b - y);
            }
            ans = min(ans, res);
        }
        cout << fixed << setprecision(3) << ans << '\n';
        cin >> n >> k;
    }
}