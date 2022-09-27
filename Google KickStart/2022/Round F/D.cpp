#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, k, x, d, m, cur, ans;
        cin >> n >> k >> x >> d >> m;
        cur = 0, ans = m;
        vector<vector<int>> start(d), end(d);
        for(int i = 0, p, l, r; i < m; i++) {
            cin >> p >> l >> r;
            start[l].push_back(p - 1);
            end[r - 1].push_back(p - 1);
        }
        map<int, int> num, best, rest;
        best[0] = k;
        if(k < n) {
            rest[0] = n - k;
        }
        auto rem_best = [&](int x) {
            --best[x];
            if(best[x] == 0) {
                best.erase(x);
            }
        };
        auto rem_rest = [&](int x) {
             --rest[x];
             if(rest[x] == 0) {
                 rest.erase(x);
             }
        };
        for(int i = 0; i < d; i++) {
            for(int p: start[i]) {
                int pv = num[p];
                if(best.count(pv)) {
                    rem_best(pv), ++best[pv + 1];
                    ++cur;
                } else {
                    rem_rest(pv), ++rest[pv + 1];
                }
                while(!rest.empty() && rest.begin()->first < (--best.end())->first) {
                    int rb = rest.begin()->first, be = (--best.end())->first;
                    rem_rest(rb), ++best[rb];
                    rem_best(be), ++rest[be];
                    cur += rb - be;
                }
                ++num[p];
            }
            if(i >= x - 1) {
                ans = min(ans, cur);
                for(int p: end[i - x + 1]) {
                    int pv = num[p];
                    if(best.count(pv)) {
                        rem_best(pv), ++best[pv - 1];
                        --cur;
                    } else {
                        rem_rest(pv), ++rest[pv - 1];
                    }
                    while(!rest.empty() && rest.begin()->first < (--best.end())->first) {
                        int rb = rest.begin()->first, be = (--best.end())->first;
                        rem_rest(rb), ++best[rb];
                        rem_best(be), ++rest[be];
                        cur += rb - be;
                    }
                    --num[p];
                }
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}