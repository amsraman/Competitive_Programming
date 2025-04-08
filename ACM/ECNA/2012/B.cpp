#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for(int _ = 1; n > 0; _++) {
        vector<pair<int, int>> pts;
        vector<int> xs, ys;
        for(int i = 0, x, y; i < n; i++) {
            cin >> x >> y;
            pts.emplace_back(x, y);
            xs.push_back(x);
            ys.push_back(y);
        }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        ll opt_dist = 0;
        for(int i = 0; i < n; i++) {
            int xmd = xs[n / 2], ymd = ys[n / 2];
            opt_dist += abs(pts[i].first - xmd) + abs(pts[i].second - ymd);
        }
        int opt_x, opt_y;
        for(int x: xs) {
            int ymd = ys[n / 2];
            ll tot_dist = 0;
            for(int i = 0; i < n; i++) {
                tot_dist += abs(pts[i].first - x) + abs(pts[i].second - ymd);
            }
            if(tot_dist == opt_dist) {
                opt_x = x;
                break;
            }
        }
        for(int y: ys) {
            ll tot_dist = 0;
            for(int i = 0; i < n; i++) {
                tot_dist += abs(pts[i].first - opt_x) + abs(pts[i].second - y);
            }
            if(tot_dist == opt_dist) {
                opt_y = y;
                break;
            }
        }
        cout << "Case " << _ << ": (" << opt_x << "," << opt_y << ") " << opt_dist << '\n';
        cin >> n;
    }
}