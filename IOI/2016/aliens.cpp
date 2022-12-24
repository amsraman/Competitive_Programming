#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll take_photos(int n, int m, int k, vector<int> r, vector<int> c) {
    vector<pair<int, int>> pts_uf, pts; // unfiltered, filtered
    for(int i = 0; i < n; i++) {
        if(r[i] > c[i]) swap(r[i], c[i]);
        pts_uf.push_back({r[i], c[i] + 1});
    }
    sort(pts_uf.begin(), pts_uf.end());
    for(int i = 0; i < n; i++) {
        while(!pts.empty() && (pts.back().first == pts_uf[i].first)) {
            pts.pop_back();
        }
        if(pts.empty() || pts.back().second < pts_uf[i].second) {
            pts.push_back(pts_uf[i]);
        }
    }
    n = pts.size();
    auto cmp = [](pair<ll, ll> f1, pair<ll, ll> f2) {
        return f1.first * f2.second < f1.second * f2.first;
    };
    auto isect = [](pair<ll, pair<ll, int>> l1, pair<ll, pair<ll, int>> l2) -> pair<ll, ll> {
        return {l2.second.first - l1.second.first, l1.first - l2.first};
    };
    auto try_penalty = [&](ll penalty) { // CHT
        vector<pair<ll, int>> dp(n + 1);
        deque<pair<ll, pair<ll, int>>> hull;
        dp[0] = {0, 0};
        hull.push_back({-2 * pts[0].first, {1LL * pts[0].first * pts[0].first, 0}});
        for(int i = 1; i <= n; i++) {
            while(hull.size() > 1 && cmp(isect(hull[0], hull[1]), {pts[i - 1].second, 1})) {
                hull.pop_front();
            }
            dp[i] = {hull[0].first * pts[i - 1].second + hull[0].second.first, hull[0].second.second};
            dp[i].first += 1LL * pts[i - 1].second * pts[i - 1].second;
            dp[i].first += penalty, dp[i].second++;
            if(i < n) { // insert line
                pair<ll, pair<ll, int>> to_add = {-2 * pts[i].first, dp[i]};
                ll df = max(0, pts[i - 1].second - pts[i].first);
                to_add.second.first += 1LL * pts[i].first * pts[i].first - df * df;
                while(hull.size() > 1 && cmp(isect(hull[hull.size() - 2], to_add), isect(hull[hull.size() - 2], hull[hull.size() - 1]))) {
                    hull.pop_back();
                }
                hull.push_back(to_add);
            }
        }
        return dp[n];
    };
    ll lb = 0, ub = 1e12;
    while(lb < ub) {
        ll mid = (lb + ub) / 2;
        pair<ll, int> res = try_penalty(mid);
        if(res.second <= k) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    pair<ll, int> res = try_penalty(ub);
    return res.first - 1LL * k * ub;
}

int main() {
    cout << take_photos(5, 7, 2, {0, 4, 4, 4, 4}, {3, 4, 6, 5, 6}) << endl;
    cout << take_photos(2, 6, 2, {1, 4}, {4, 1}) << endl;
}