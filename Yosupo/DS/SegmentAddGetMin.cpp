// 985 ms
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 2e18;

template <typename T, class L>
struct LiChaoTree {
    // Coordinate Compressed Version
    int n, log, sz;
    const T INF = numeric_limits<T>::max();
    vector<T> coords;
    vector<L> seg;

    LiChaoTree(const vector<T> & coords): n(coords.size()), log(__lg(max(n - 1, 1)) + 1), sz(1 << log), coords(coords) {
        seg.resize(sz << 1, {0, INF});
    }

    T query(T pos) {
        int ind = lower_bound(coords.begin(), coords.end(), pos) - coords.begin();
        T ret = INF;
        for(ind += sz; ind > 0; ind >>= 1) {
            ret = min(ret, seg[ind - 1](pos));
        }
        return ret;
    }

    void add(int lo, int hi, L line, int lo_ind, int hi_ind, int ind) {
        if(hi_ind <= lo || hi <= lo_ind) {
            return;
        } else if(lo <= lo_ind && hi_ind <= hi) {
            int mid = (lo_ind + hi_ind) >> 1;
            T pos = coords[mid];
            if(seg[ind](pos) > line(pos)) swap(seg[ind], line);
            if(lo_ind + 1 == hi_ind) return;
            if(line < seg[ind]) {
                add(lo, hi, line, lo_ind, mid, 2 * ind + 1);
            } else {
                add(lo, hi, line, mid, hi_ind, 2 * ind + 2);
            }
        } else {
            int mid = (lo_ind + hi_ind) >> 1;
            add(lo, hi, line, lo_ind, mid, 2 * ind + 1);
            add(lo, hi, line, mid, hi_ind, 2 * ind + 2);
        }
    }

    void add(int lo, int hi, L line) {
        lo = lower_bound(coords.begin(), coords.end(), lo) - coords.begin();
        hi = lower_bound(coords.begin(), coords.end(), hi) - coords.begin();
        add(lo, hi, line, 0, sz, 0);
    }

    void add(L line) {
        add(0, sz, line, 0, sz, 0);
    }
};

struct Line {
    ll m, b;
    ll operator()(ll x) {
        return m * x + b;
    }
    bool operator<(const Line & L) {
        return m > L.m;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<ll> coords;
    vector<array<ll, 5>> queries(n + q);
    for(int i = 0; i < n; i++) {
        cin >> queries[i][1] >> queries[i][2] >> queries[i][3] >> queries[i][4];
        queries[i][0] = 0;
        coords.push_back(queries[i][1]), coords.push_back(queries[i][2]);
    }
    for(int i = n; i < n + q; i++) {
        cin >> queries[i][0];
        if(queries[i][0]) {
            cin >> queries[i][1];
            coords.push_back(queries[i][1]);
        } else {
            cin >> queries[i][1] >> queries[i][2] >> queries[i][3] >> queries[i][4];
            coords.push_back(queries[i][1]), coords.push_back(queries[i][2]);
        }
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    LiChaoTree<ll, Line> tr(coords);
    for(array<ll, 5> qr: queries) {
        if(qr[0]) {
            ll ret = tr.query(qr[1]);
            if(ret == INF) {
                cout << "INFINITY\n";
            } else {
                cout << ret << '\n';
            }
        } else {
            tr.add(qr[1], qr[2], {qr[3], qr[4]});
        }
    }
}