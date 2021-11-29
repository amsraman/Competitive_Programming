#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define f first
#define s second

using namespace std;

const ld epsilon = 1e-6, PI = acosl(-1);

template<typename T>
struct FenwickTree {
    int n;
    vector<T> bit;

    FenwickTree(int n): n(n), bit(n, 0) {};

    T qry(int x) {
        T ret = 0;
        for(x++; x > 0; x -= (x & -x)) {
            ret += bit[x - 1];
        }
        return ret;
    }

    T qry(int x, int y) {
        return qry(y) - qry(x - 1);
    }

    void upd(int x, T k) {
        for(x++; x <= n; x += (x & -x)) {
            bit[x - 1] += k;
        }
    }
};

int n;
ll k;
pair<int, int> points[100000];
pair<ld, ld> ang[100000];

ld dist(pair<ld, ld> p1, pair<ld, ld> p2) {
    return sqrt((p1.f - p2.f) * (p1.f - p2.f) + (p1.s - p2.s) * (p1.s - p2.s));
}

ld norm(ld a) {
    while(a < 0) {
        a += 2 * PI;
    } 
    while(a > 2 * PI) {
        a -= 2 * PI;
    }
    return a;
}

bool ok(ld rad) {
    ll tot = (long long) n * (n - 1) / 2;
    set<pair<ld, pair<int, int>>> chords;
    vector<ld> coords;
    for(int i = 0; i < n; i++) {
        ld dst = dist({0, 0}, points[i]);
        if(dst > rad) {
            ld cent = atan2(points[i].s, points[i].f), side = acosl(rad / dist({0, 0}, points[i]));
            ang[i] = {norm(cent - side), norm(cent + side)};
            if(ang[i].s < ang[i].f) {
                swap(ang[i].f, ang[i].s);
            }
        } else {
            ang[i] = {-2 * i - 2, -2 * i - 1};
        }
        chords.insert({ang[i].f, {i, 1}}), chords.insert({ang[i].s, {i, -1}});
        coords.push_back(ang[i].f), coords.push_back(ang[i].s);
    }
    sort(coords.begin(), coords.end());
    auto get_ind = [&] (ld c) {
        return lower_bound(coords.begin(), coords.end(), c) - coords.begin();
    };
    FenwickTree<ll> ft(2 * n);
    for(pair<ld, pair<int, int>> p: chords) {
        if(p.s.s == 1) {
            ft.upd(get_ind(p.f), 1);
        } else if(p.s.s == -1) {
            ft.upd(get_ind(ang[p.s.f].f), -1);
            tot -= ft.qry(get_ind(ang[p.s.f].f), get_ind(ang[p.s.f].s));
        }
    }
    return tot >= k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> points[i].f >> points[i].s;
    }
    ld lb = 0, ub = 1e5;
    while((ub - lb) > epsilon) {
        ld mid = (lb + ub) / 2;
        if(ok(mid)) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    cout << fixed << setprecision(7) << ub << '\n';
}