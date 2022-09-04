#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int INF = 0x3f3f3f3f, state_count = 40002;

int n, eq_classes = 3, ang[200], side[200], id[200][200], dp[200][200][200][2], ans;
pair<int, int> pts[200];
vector<pair<int, int>> ranges[state_count];

int main() {
    ifstream cin("lightsout.in");
    ofstream cout("lightsout.out");
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> pts[i].f >> pts[i].s;
    }
    for(int i = 0; i < n; i++) {
        pair<int, int> pv = pts[(i + n - 1) % n], cur = pts[i], nxt = pts[(i + 1) % n];
        ll cross = 1LL * (nxt.s - cur.s) * (cur.f - pv.f) - 1LL * (nxt.f - cur.f) * (cur.s - pv.s);
        ang[i] = (cross > 0 ? 1 : 0);
        if(i == 0) {
            ang[i] = 2;
        }
        ranges[ang[i]].push_back({i, i}), id[i][i] = ang[i];
        side[i] = abs(cur.f - pv.f) + abs(cur.s - pv.s) + (i > 0 ? side[i - 1] : 0);
    }
    auto get_sum = [&](int x, int y) {
        if(x <= y) {
            return side[y] - side[x];
        }
        return side[n - 1] - side[x] + side[y];
    };
    for(int i = 0; i < eq_classes; i++) {
        if(ranges[i].size() <= 1) {
            continue;
        }
        vector<pair<pair<int, int>, pair<int, int>>> adj;
        for(pair<int, int> r: ranges[i]) {
            int nxt = (r.s + 1) % n;
            adj.push_back({{get_sum(r.s, nxt), ang[nxt]}, {r.f, nxt}});
        }
        sort(adj.begin(), adj.end());
        pair<int, int> pv = {-1, -1};
        for(pair<pair<int, int>, pair<int, int>> r: adj) {
            if(r.f != pv) {
                pv = r.f, eq_classes++;
            }
            ranges[eq_classes - 1].push_back(r.s), id[r.s.f][r.s.s] = eq_classes - 1;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j && id[i][j] == 0) {
                ranges[eq_classes++].push_back({i, j}), id[i][j] = eq_classes - 1;
            }
        }
    }
    for(int i = 0; i < eq_classes; i++) {
        if(ranges[i].size() == 1) {
            pair<int, int> r = ranges[i][0];
            for(int j = r.f; j != (r.s + 1) % n; j = (j + 1) % n) {
                dp[r.f][r.s][j][0] = min(get_sum(r.f, 0), get_sum(0, r.f)) - min(get_sum(0, j), get_sum(j, 0));
                dp[r.f][r.s][j][1] = min(get_sum(r.s, 0), get_sum(0, r.s)) - min(get_sum(0, j), get_sum(j, 0));
            }
        }
    }
    for(int i = eq_classes - 1; i >= 0; i--) {
        if(ranges[i].size() <= 1) {
            continue;
        }
        int sz = ranges[i][0].s - ranges[i][0].f + 1;
        for(int j = 0; j < sz; j++) {
            for(int side = 0; side < 2; side++) {
                int mx_left = -INF, mx_right = -INF;
                for(pair<int, int> r: ranges[i]) {
                    int loc = (side == 0 ? r.f : r.s), pv = (r.f + n - 1) % n, nxt = (r.s + 1) % n;
                    mx_left = max(mx_left, dp[pv][r.s][r.f + j][0] + get_sum(pv, loc));
                    mx_right = max(mx_right, dp[r.f][nxt][r.f + j][1] + get_sum(loc, nxt));
                }
                for(pair<int, int> r: ranges[i]) {
                    int loc = (side == 0 ? r.f : r.s), pv = (r.f + n - 1) % n, nxt = (r.s + 1) % n;
                    if(mx_left <= mx_right) {
                        dp[r.f][r.s][r.f + j][side] = dp[pv][r.s][r.f + j][0] + get_sum(pv, loc);
                    } else {
                        dp[r.f][r.s][r.f + j][side] = dp[r.f][nxt][r.f + j][1] + get_sum(loc, nxt);
                    }
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        ans = max(ans, dp[i][i][i][0]);
    }
    cout << ans << endl;
}