#include <bits/stdc++.h>

using namespace std;

using fl = long double;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int l, s, d, n; cin >> l >> s >> d >> n;
    for(int tc = 1; d != 0; tc++) {
        vector<pair<fl, int>> cars;
        for(int i = 0, cl, cs; i < n; i++) {
            cin >> cl >> cs; cars.emplace_back(cl, cs);
        }
        auto in_range = [&](fl x, fl y, fl z) {
            return x <= y && y <= z;
        };
        fl cur_tm = 0, cur_pos = l; int cur_speed = s;
        while(true) {
            int tot_speed = cur_speed, num_hits = 1;
            for(int i = 0; i < n; i++) {
                if(in_range(cur_pos - 1, cars[i].first, cur_pos)) {
                    tot_speed += cars[i].second; ++num_hits;
                }
            }
            cur_speed = tot_speed / num_hits;
            fl time_to_dest = cur_tm + (cur_pos * -1 + d) / cur_speed, nxt_hit = 1e18;
            for(auto [cl, cs]: cars) {
                if(cs == cur_speed) continue;
                fl nxt_me = cur_pos + fl(cur_speed) / 4, nxt_them = cl + fl(cs) / 4;
                if((cs < cur_speed && nxt_them + 1 < nxt_me) || (cs > cur_speed && nxt_me < nxt_them)) {
                    continue;
                }
                if(in_range(nxt_me - 1, nxt_them, nxt_me)) {
                    nxt_hit = cur_tm + fl(1) / 4;
                    break;
                } else if(nxt_them + 1 < nxt_me) { // they will catch up
                    assert(cur_speed < cs);
                    fl dist = nxt_me - nxt_them - 1, tm = dist / (cs - cur_speed);
                    tm = ceil(tm * 4) / 4;
                    if(in_range(nxt_me + tm * cur_speed - 1, nxt_them + tm * cs, nxt_me + tm * cur_speed)) {
                        nxt_hit = min(nxt_hit, tm + cur_tm + fl(1) / 4);
                    }
                } else { // I will catch up
                    assert(cs < cur_speed);
                    fl dist = nxt_them - nxt_me, tm = dist / (cur_speed - cs);
                    tm = ceil(tm * 4) / 4;
                    if(in_range(nxt_me + tm * cur_speed - 1, nxt_them + tm * cs, nxt_me + tm * cur_speed)) {
                        nxt_hit = min(nxt_hit, tm + cur_tm + fl(1) / 4);
                    }
                }
            }
            if(nxt_hit > time_to_dest) {
                cur_tm = time_to_dest;
                break;
            }
            for(int i = 0; i < n; i++) {
                cars[i].first += (nxt_hit - cur_tm) * cars[i].second;
            }
            cur_pos += (nxt_hit - cur_tm) * cur_speed; cur_tm = nxt_hit;
        }
        cout << "Case " << tc <<  ": Anna reaches her destination at time ";
        cout << fixed << setprecision(4) << cur_tm;
        cout << " at a speed of " << cur_speed << endl;
        cin >> l >> s >> d >> n;
    }
}