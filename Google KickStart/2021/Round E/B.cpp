#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll r, c, k, r1, c1, r2, c2;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> r >> c >> k >> r1 >> c1 >> r2 >> c2;
        --r1, --c1;
        ll num_cuts = 0, init_cuts = 1e18;
        ll h1 = (r1 == 0 ? 0 : (c2 - c1 + k - 1) / k);
        ll h2 = (r2 == r ? 0 : (c2 - c1 + k - 1) / k);
        ll v1 = (c1 == 0 ? 0 : (r2 - r1 + k - 1) / k);
        ll v2 = (c2 == c ? 0 : (r2 - r1 + k - 1) / k);
        init_cuts = min(init_cuts, (r1 == 0 ? 0 : min((c2 + k - 1) / k, (c - c1 + k - 1) / k)) + h2 + v1 + v2);
        init_cuts = min(init_cuts, (r2 == r ? 0 : min((c2 + k - 1) / k, (c - c1 + k - 1) / k)) + h1 + v1 + v2);
        init_cuts = min(init_cuts, (c1 == 0 ? 0 : min((r2 + k - 1) / k, (r - r1 + k - 1) / k)) + h1 + h2 + v2);
        init_cuts = min(init_cuts, (c2 == c ? 0 : min((r2 + k - 1) / k, (r - r1 + k - 1) / k)) + h1 + h2 + v1);
        num_cuts = init_cuts;
        ll sub_divide = 1e18;
        ll h = r2 - r1, v = c2 - c1;
        ll cracks = (h + k - 1) / k - 1;
        sub_divide = min(sub_divide, (v - 1) * ((h + k - 1) / k) + v * (h - 1 - cracks) + cracks * ((v + k - 1) / k));
        cracks = (v + k - 1) / k - 1;
        sub_divide = min(sub_divide, (h - 1) * ((v + k - 1) / k) + h * (v - 1 - cracks) + cracks * ((h + k - 1) / k));
        num_cuts += sub_divide;
        assert(num_cuts >= 0);
        cout << "Case #" << _ << ": " << num_cuts << endl;
    }
}