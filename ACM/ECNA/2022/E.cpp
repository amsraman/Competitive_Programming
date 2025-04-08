#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int k; cin >> k;
    while(k--) {
        int n; ll x1, y1, x2, y2; cin >> n >> x1 >> y1 >> x2 >> y2;
        ll ans = 0; bool done = false;
        auto dist = [](pair<ll, ll> p1, pair<ll, ll> p2) {
            return abs(p1.first - p2.first) + abs(p1.second - p2.second);
        };
        auto in_box = [](optional<pair<ll, ll>> pt, ll ub) -> optional<pair<ll, ll>> {
            if(!pt) return pt;
            auto [x, y] = pt.value();
            if(min(x, y) < 0 || max(x, y) >= ub) return nullopt;
            return pt;
        };
        auto get_transform = [](optional<pair<ll, ll>> pt, int n) -> optional<tuple<ll, ll, int>> {
            if(!pt) return nullopt;
            ll mid = 1LL << (n - 1);
            auto [x, y] = pt.value(); int rot = (y >= mid ? 0 : 1 + 2 * (x >= mid));
            return make_tuple(mid * (x >= mid), mid * (y >= mid), rot);
        };
        auto apply_transform = [](optional<pair<ll, ll>> pt, int n, optional<tuple<ll, ll, int>> transform, bool inv = false) -> optional<pair<ll, ll>> {
            if(!pt) return nullopt;
            ll box = (1LL << (n - 1)) - 1;
            auto [x, y] = pt.value();
            auto [dx, dy, rot] = transform.value();
            if(!inv) {
                x -= dx, y -= dy;
                for(int i = 0; i < rot; i++) tie(x, y) = make_pair(box - y - 1, x);
            } else {
                for(int i = 0; i < 4 - rot; i++) tie(x, y) = make_pair(box - y - 1, x);
                x += dx, y += dy;
            }
            return make_pair(x, y);
        };
        auto escape = [](optional<pair<ll, ll>> pt, int n) -> optional<pair<ll, ll>> {
            if(!pt) return nullopt;
            auto [x, y] = pt.value();
            ll mid = (1LL << (n - 1)) - 1, ub = 2 * mid + 1;
            if(x != mid && y != mid) return nullopt;
            return y > mid ? make_pair(mid, ub) : make_pair(mid, -1LL);
        };
        auto move_to_escape = [&](optional<pair<ll, ll>> pt, optional<pair<ll, ll>> targ) {
            if(!pt || !targ) return pt;
            if(!done) ans += dist(pt.value(), targ.value());
            return targ;
        };
        auto go = [&](auto rec, int lev, optional<pair<ll, ll>> p1, optional<pair<ll, ll>> p2, bool same) -> pair<optional<pair<ll, ll>>, optional<pair<ll, ll>>> {
            ll mid = (1LL << (lev - 1)) - 1, ub = 2 * mid + 1;
            p1 = in_box(p1, ub), p2 = in_box(p2, ub);
            if(!p1 && !p2) return make_pair(nullopt, nullopt);
            if(lev > 1) {
                auto t1 = get_transform(p1, lev), t2 = get_transform(p2, lev);
                auto [r1, r2] = rec(rec, lev - 1, apply_transform(p1, lev, t1), apply_transform(p2, lev, t2), same && (t1 == t2));
                r1 = apply_transform(r1, lev, t1, true), r2 = apply_transform(r2, lev, t2, true);
                if(r1) p1 = r1;
                if(r2) p2 = r2;
            }
            optional<pair<ll, ll>> c1 = escape(p1, lev), c2 = escape(p2, lev);
            if(same && !done && c1.has_value() && c2.has_value() && c1 == c2) {
                ans += dist(p1.value(), p2.value());
                done = true;
            }
            return make_pair(move_to_escape(p1, c1), move_to_escape(p2, c2));
        };
        pair<ll, ll> p1 = make_pair(x1, y1), p2 = make_pair(x2, y2);
        auto [r1, r2] = go(go, n, p1, p2, true);
        if(r1) p1 = r1.value();
        if(r2) p2 = r2.value();
        tie(x1, y1) = p1; tie(x2, y2) = p2;
        if(min(x1, x2) < 0 && max(x1, x2) >= (1LL << n) - 1 && min(y1, y2) >= 0 && max(y1, y2) < (1LL << n) - 1) {
            if(x1, x2) swap(p1, p2);
            ans += min(dist(p1, {0, -1}) + dist({0, -1}, p2), dist(p1, {0, (1LL << n) - 1}) + dist({0, (1LL << n) - 1}, p2));
        } else if(min(y1, y2) < 0 && max(y1, y2) >= (1LL << n) - 1 && min(x1, x2) >= 0 && max(x1, x2) < (1LL << n) - 1) {
            if(y1 > y2) swap(p1, p2);
            ans += min(dist(p1, {-1, 0}) + dist({-1, 0}, p2), dist(p1, {(1LL << n) - 1, 0}) + dist({(1LL << n) - 1, 0}, p2));
        } else {
            ans += dist(p1, p2);
        }
        cout << ans << '\n';
    }
}