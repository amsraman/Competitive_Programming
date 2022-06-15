// 301 ms
#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mod = 998244353;

template<class B>
struct SegTree : public B {
    using T = typename B::T;

    int n, sz, log;
    vector<T> seg;

    SegTree(int n): n(n), log(__lg(max(n - 1, 1)) + 1) {
        sz = (1 << log), seg.resize(sz << 1, B::e);
    };

    SegTree(vector<T> & init): n((int) init.size()), log(__lg(max(n - 1, 1)) + 1) {
        sz = (1 << log), seg.resize(sz << 1, B::e);
        copy(init.begin(), init.end(), seg.begin() + sz);
        for(int i = sz - 1; i > 0; i--) {
            seg[i] = B::comb(seg[2 * i], seg[2 * i + 1]);
        }
    };

    T qry(int lo, int hi) {
        T ret1 = B::e, ret2 = B::e;
        for(lo += sz, hi += sz; lo <= hi; lo >>= 1, hi >>= 1) {
            if(lo & 1) {
                ret1 = B::comb(ret1, seg[lo++]);
            }
            if(hi & 1 ^ 1) {
                ret2 = B::comb(seg[hi--], ret2);
            }
        }
        return B::comb(ret1, ret2);
    }

    void upd(int ind, T val) {
        seg[ind += sz] = val;
        while(ind > 1) {
            ind >>= 1;
            seg[ind] = B::comb(seg[2 * ind], seg[2 * ind + 1]);
        }
    }
};

struct Info {
    using T = pair<int, int>;
    const T e = {1, 0};

    T comb(T a, T b) {
        return {(1LL * a.f * b.f) % mod, (1LL * b.f * a.s + b.s) % mod};
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].f >> a[i].s;
    }
    SegTree<Info> seg(a);
    while(q--) {
        int type;
        cin >> type;
        if(type == 0) {
            int p, c, d;
            cin >> p >> c >> d;
            seg.upd(p, {c, d});
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            pair<int, int> eq = seg.qry(l, r - 1);
            cout << (1LL * eq.f * x + eq.s) % mod << '\n';
        }
    }
}