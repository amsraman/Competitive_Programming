#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t;
ll vx[4], vy[4];
pair<int, int> p[4];

ll try_corner(ll lx, ll ly, ll x) {
    ll p1 = abs(p[0].f - lx) + abs(p[0].s - ly);
    ll p2 = abs(p[1].f - (lx + x)) + abs(p[1].s - ly);
    ll p3 = abs(p[2].f - lx) + abs(p[2].s - (ly + x));
    ll p4 = abs(p[3].f - (lx + x)) + abs(p[3].s - (ly + x));
    return p1 + p2 + p3 + p4;
}

ll cost(ll x) {
    vx[0] = p[0].f;
    vx[1] = p[1].f - x;
    vx[2] = p[2].f;
    vx[3] = p[3].f - x;
    vy[0] = p[0].s;
    vy[1] = p[1].s;
    vy[2] = p[2].s - x;
    vy[3] = p[3].s - x;
    sort(vx, vx + 4);
    sort(vy, vy + 4);
    return try_corner((vx[1] + vx[2]) / 2, (vy[1] + vy[2]) / 2, x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        for(int i = 0; i < 4; i++) {
            cin >> p[i].f >> p[i].s;
        }
        sort(p, p + 4);
        ll ans = 0xffffffffff;
        do {
            ll lb = 0, ub = 2e10;
            while(lb < ub) {
                ll mid = (lb + ub) / 2;
                if(cost(mid) < cost(mid + 1)) {
                    ub = mid;
                } else {
                    lb = mid + 1;
                }
            }
            ans = min(ans, cost(ub));
        } while(next_permutation(p, p + 4));
        cout << ans << '\n';
    }
}