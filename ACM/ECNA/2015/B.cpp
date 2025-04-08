#include <bits/stdc++.h>

using namespace std;

int main() {
    int nr, nc, n, m; cin >> nr >> nc >> n >> m;
    vector<tuple<int, int, int>> wind;
    vector<int> xs;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        wind.emplace_back(x + 7, y + 4, 1);
        if(x + 7 < nr) xs.push_back(x + 7);
    }
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        wind.emplace_back(x + 7, y + 4, 0);
        if(x + 7 < nr) xs.push_back(x + 7);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    int sz = (int) xs.size(), ans = n;
    for(int i = 0; i < sz; i++) {
        for(int j = i; j < sz; j++) {
            int black_inside = 0, black_outside = 0;
            map<int, int> inside_pts;
            for(auto [x, y, tp]: wind) {
                if(xs[i] <= x && x <= xs[j]) {
                    black_inside += tp;
                    if(y < nc) inside_pts[y] += (tp == 1 ? -1 : 1);
                } else {
                    black_outside += tp;
                }
            }
            int cur = 0, mn = 0;
            for(auto [k, v]: inside_pts) {
                cur = min(0, cur + v);
                mn = min(mn, cur);
            }
            ans = min(ans, black_outside + black_inside + mn);
        }
    }
    cout << ans << '\n';
}