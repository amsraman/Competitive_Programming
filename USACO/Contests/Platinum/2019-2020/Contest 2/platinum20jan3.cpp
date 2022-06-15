#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    ifstream cin("falling.in");
    ofstream cout("falling.out");
    int n;
    cin >> n;
    vector<int> a(n), q(n), pos(n);
    vector<pair<int, int>> lines(n), ans(n, {-1, 1});
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> q[i];
        --q[i];
    }
    for(int i = 0; i < n; i++) {
        lines[i] = {a[i], -i - 1};
    }
    sort(lines.begin(), lines.end());
    for(int i = 0; i < n; i++) {
        pos[-lines[i].s - 1] = i;
    }
    deque<int> hull[2];
    auto frac_compare = [](pair<int, int> a, pair<int, int> b) {
        ll res1 = 1LL * a.f * b.s, res2 = 1LL * a.s * b.f;
        if(res1 < res2) {
            return -1;
        } else if(res1 > res2) {
            return 1;
        }
        return 0;
    };
    auto intersection = [&](int a, int b) {
        int sgn = (lines[b].s < lines[a].s ? -1 : 1);
        return make_pair(sgn * (lines[a].f - lines[b].f), sgn * (lines[b].s - lines[a].s));
    };
    auto query = [&](int h, int l) {
        int lb = 0, ub = hull[h].size() - 1;
        while(lb < ub) {
            int mid = (lb + ub + 1) / 2; 
            pair<int, int> pv_intersection = intersection(hull[h][mid - 1], hull[h][mid]);
            pair<int, int> cur_intersection = intersection(l, hull[h][mid]);
            if(cur_intersection.f < 0) {
                cur_intersection = {INF, 1};
            }
            if(frac_compare(pv_intersection, cur_intersection) <= 0) {
                lb = mid;
            } else {
                ub = mid - 1;
            }
        }
        return intersection(l, hull[h][ub]);
    };
    // 0: max hull, 1: min hull
    for(int i = 0; i < n; i++) {
        for(int j = 0, cur = i, sgn = 1; j < 2; j++, cur = n - i - 1, sgn = -1) {
            while(hull[j].size() > 0 && lines[cur].s * sgn > lines[hull[j][0]].s * sgn) {
                hull[j].pop_front();
            }
            while(hull[j].size() > 1 && frac_compare(intersection(cur, hull[j][1]), intersection(hull[j][0], hull[j][1])) >= 0) {
                hull[j].pop_front();
            }
            hull[j].push_front(cur);
            int quer = q[-lines[cur].s - 1];
            if(a[quer] * sgn > lines[cur].f * sgn) {
                ans[-lines[cur].s - 1] = query(j, pos[quer]);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(ans[i].f < 0) {
            cout << -1;
        } else {
            ll g = __gcd(ans[i].f, ans[i].s);
            cout << ans[i].f / g << '/' << ans[i].s / g;
        }
        cout << '\n';
    }
}