#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, e;
        cin >> n >> e;
        map<int, vector<array<int, 3>>> ev;
        map<int, ll> pf, sf;
        vector<vector<ll>> dp(n, vector<ll>(2, 0));
        for(int i = 0, x, y, c; i < n; i++) {
            cin >> x >> y >> c;
            ev[-y].push_back({x, c, i});
        }
        pf[-1] = 0, sf[1e9 + 1] = -0xfffffffffffffff;
        ll ans = 0;
        for(auto it: ev) {
            vector<array<int, 3>> pts = it.second;
            sort(pts.begin(), pts.end());
            ll mx0 = (--pf.end())->second, mx1 = (sf.begin())->second;
            for(array<int, 3> p: pts) {
                dp[p[2]][0] = mx1 + p[1] - e;
                if(!pf.empty()) {
                    auto it = --pf.upper_bound(p[0]);
                    dp[p[2]][0] = max(dp[p[2]][0], it->second + p[1]);
                }
                auto it = pf.upper_bound(p[0]);
                while(it != pf.end() && it->second <= dp[p[2]][0]) {
                    pf.erase(it++);
                }
                pf[p[0]] = dp[p[2]][0];
                ans = max(ans, dp[p[2]][0]);
            }
            reverse(pts.begin(), pts.end());
            for(array<int, 3> p: pts) {
                dp[p[2]][1] = mx0 + p[1] - e;
                if(!sf.empty()) {
                    auto it = sf.lower_bound(p[0]);
                    dp[p[2]][1] = max(dp[p[2]][1], it->second + p[1]);
                }
                auto it = sf.lower_bound(p[0]);
                while(it != sf.begin() && prev(it)->second <= dp[p[2]][1]) {
                    sf.erase(prev(it));
                }
                sf[p[0]] = dp[p[2]][1];
                ans = max(ans, dp[p[2]][1]);
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}