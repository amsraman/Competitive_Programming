#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 1e9 + 7;

struct Line {
    ll m, b;
    mutable ll ep;
    bool operator<(const Line & l) const {
        return m < l.m;
    }
    bool operator<(ll x) const {
        return ep < x;
    }
};

struct LineContainer : multiset<Line, less<>> {
    static const ll INF = LLONG_MAX;
    ll div(ll x, ll y) {
        return x / y - ((x ^ y) < 0 && x % y);
    }
    bool upd(iterator x, iterator y) {
        if(y == end()) {
            x->ep = INF;
            return false;
        }
        if(x->m == y->m) {
            x->ep = (x->b < y->b ? -INF : INF);
        } else {
            x->ep = div(x->b - y->b, y->m - x->m);
        }
        return x->ep >= y->ep;
    }
    void add(ll m, ll b) {
        auto z = insert({m, b, 0}), y = z++, x = y;
        while(upd(y, z)) {
            z = erase(z);
        }
        if(x != begin() && upd(--x, y)) {
            upd(x, y = erase(y));
        }
        while((y = x) != begin() && (--x)->ep >= y->ep) {
            upd(x, erase(y));
        }
    }
    ll query(ll x) {
        assert(!empty());
        auto it = *lower_bound(x);
        return it.m * x + it.b;
    }
};

int main() {
    ifstream cin("log_drivin_hirin_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m, k, ans = 1;
        cin >> n >> m >> k;
        vector<int> p(n), l(n), h(n), x(m), y(m);
        vector<ll> offset(n, 0);
        vector<vector<int>> g(n), q(n);
        int ap, bp, cp, al, bl, cl, dl, ah, bh, ch, dh, ax, bx, cx, ay, by, cy, dy;
        for(int i = 0; i < k; i++) {
            cin >> p[i];
        }
        cin >> ap >> bp >> cp;
        for(int i = 0; i < k; i++) {
            cin >> l[i];
        }
        cin >> al >> bl >> cl >> dl;
        for(int i = 0; i < k; i++) {
            cin >> h[i];
        }
        cin >> ah >> bh >> ch >> dh;
        for(int i = 0; i < k; i++) {
            cin >> x[i];
        }
        cin >> ax >> bx >> cx;
        for(int i = 0; i < k; i++) {
            cin >> y[i];
        }
        cin >> ay >> by >> cy >> dy;
        for(int i = k; i < n; i++) {
            p[i] = (1LL * ap * p[i - 2] + 1LL * bp * p[i - 1] + cp) % i + 1;
            l[i] = (1LL * al * l[i - 2] + 1LL * bl * l[i - 1] + cl) % dl + 1;
            h[i] = (1LL * ah * h[i - 2] + 1LL * bh * h[i - 1] + ch) % dh + 1;
        }
        for(int i = k; i < m; i++) {
            x[i] = (1LL * ax * x[i - 2] + 1LL * bx * x[i - 1] + cx) % n + 1;
            y[i] = (1LL * ay * y[i - 2] + 1LL * by * y[i - 1] + cy) % dy + 1;
        }
        for(int i = 0; i < m; i++) {
            q[x[i] - 1].push_back(y[i]);
        }
        vector<LineContainer> hull(n);
        for(int i = n - 1; i >= 0; i--) {
            if(i > 0) {
                g[p[i] - 1].push_back(i);
            }
            if(g[i].empty()) {
                hull[i].add(0, 0);
            } else {
                for(int u: g[i]) {
                    if(hull[u].size() > hull[i].size()) {
                        swap(hull[i], hull[u]), swap(offset[i], offset[u]);
                    }
                }
                for(int u: g[i]) {
                    offset[u] -= offset[i];
                    for(Line l: hull[u]) {
                        hull[i].add(l.m - offset[u], l.b);
                    }
                    hull[u].clear();
                }
                ll mn = hull[i].query(h[i]);
                hull[i].add(offset[i], -1LL * offset[i] * h[i] + mn);
            }
            for(int y: q[i]) {
                ans = (1LL * ans * ((-hull[i].query(y) + 1LL * y * offset[i] + 1) % mod)) % mod;
            }
            offset[i] += l[i];
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}

