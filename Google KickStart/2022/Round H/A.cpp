#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int l, n, ans = 0, cur = 0;
        char ld;
        cin >> l >> n;
        vector<pair<int, char>> run(n);
        for(int i = 0; i < n; i++) {
            cin >> run[i].first >> run[i].second;
            if(cur == 0) ld = run[i].second;
            if(run[i].second == 'C' && cur + run[i].first >= l) {
                int fst = min(run[i].first, l - cur);
                run[i].first -= fst;
                ans += (ld == 'C') + run[i].first / l;
                ld = 'C', cur = run[i].first % l;
            } else if(run[i].second == 'A' && cur - run[i].first <= 0) {
                int fst = min(run[i].first, cur);
                run[i].first -= fst;
                ans += (ld == 'A' && cur != 0) + run[i].first / l;
                ld = 'A', cur = (l - (run[i].first % l)) % l;
            } else {
                cur += run[i].first * (run[i].second == 'C' ? 1 : -1);
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}