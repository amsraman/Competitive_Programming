#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for(int _ = 1; n > 0; _++) {
        vector<tuple<int, int, int>> dim;
        for(int i = 0, a, b, c; i < n; i++) {
            cin >> a >> b >> c;
            dim.emplace_back(a, b, c);
        }
        int mx = 0;
        auto gen = [&](auto rec, int lev) -> void {
            if(lev == n) {
                vector<tuple<int, int, int>> rects = dim;
                for(int i = 0; i < n; i++) {
                    auto [a, b, c] = rects[i];
                    if(a < b) rects[i] = {b, a, c};
                }
                sort(rects.begin(), rects.end());
                reverse(rects.begin(), rects.end());
                vector<int> dp(n, 1);
                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < i; j++) {
                        auto [a1, b1, c1] = rects[j];
                        auto [a2, b2, c2] = rects[i];
                        if(a1 >= a2 && b1 >= b2 || b1 >= a2 && a1 >= b2) {
                            dp[i] = max(dp[i], dp[j] + 1);
                        }
                    }
                    mx = max(mx, dp[i]);
                }
                return;
            }
            for(int i = 0; i < 3; i++) {
                auto [a, b, c] = dim[lev];
                dim[lev] = {b, c, a};
                rec(rec, lev + 1);
            }
        };
        gen(gen, 0);
        cout << "Case " << _ << ": " << mx << '\n';
        cin >> n;
    }
}