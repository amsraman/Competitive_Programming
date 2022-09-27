#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 2e18;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, x;
        ll d, ans = 0;
        cin >> d >> n >> x;
        vector<array<ll, 3>> seeds(n);
        vector<ll> coords;
        set<pair<ll, ll>> intervals;
        for(int i = 0; i < n; i++) {
            cin >> seeds[i][1] >> seeds[i][2] >> seeds[i][0];
            coords.push_back(max(0LL, d - seeds[i][2]));
        }
        sort(seeds.begin(), seeds.end());
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        if(coords[0] != 0) {
            intervals.insert({coords[0], coords[0] * x});
        }
        for(int i = 0; i + 1 < coords.size(); i++) {
            intervals.insert({coords[i + 1], (coords[i + 1] - coords[i]) * x});
        }
        for(int i = n - 1; i >= 0; i--) {
            int num_left = seeds[i][1];
            while(true) {
                auto it = intervals.lower_bound({d - seeds[i][2], INF});
                if(it == intervals.begin()) {
                    break;
                }
                pair<ll, ll> cur = *prev(it);
                intervals.erase(prev(it));
                ll to_take = min(cur.s, 1LL * num_left);
                cur.s -= to_take, num_left -= to_take, ans += to_take * seeds[i][0];
                if(cur.s != 0) {
                    intervals.insert(cur);
                }
                if(num_left == 0) {
                    break;
                }
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}