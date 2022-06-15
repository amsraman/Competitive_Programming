#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

template<class B>
struct LazySegTree : public B {
    using T_q = typename B::T_q;
    using T_u = typename B::T_u;

    size_t n, sz, log;
    vector<T_q> seg, init;
    vector<T_u> lazy;

    LazySegTree(size_t n): n(n), log(__lg(max((int) n - 1, 1)) + 1) {
        sz = (1 << log), seg.resize(sz << 1, B::e_q), lazy.resize(sz << 1, B::e_u);
    }

    LazySegTree(vector<T_q> & init): n(init.size()), init(init), log(__lg(max((int) n - 1, 1)) + 1) {
        sz = (1 << log), seg.resize(sz << 1, B::e_q), lazy.resize(sz << 1, B::e_u);
        bld(0, n - 1, 0);
    }

    void bld(int lo, int hi, int ind) {
        if(lo == hi) {
            seg[ind] = init[lo];
            return;
        }
        int mid = (lo + hi) >> 1;
        bld(lo, mid, 2 * ind + 1);
        bld(mid + 1, hi, 2 * ind + 2);
        seg[ind] = B::comb(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void app(int ind, int lo, int hi, T_u delta) {
        seg[ind] = B::upd(seg[ind], delta, lo, hi);
        lazy[ind] = B::comb_upd(delta, lazy[ind]);
    }

    void push(int ind, int lo, int hi) {
        if(lo != hi) {
            int mid = (lo + hi) >> 1;
            app(2 * ind + 1, lo, mid, lazy[ind]);
            app(2 * ind + 2, mid + 1, hi, lazy[ind]);
        }
        lazy[ind] = B::e_u;
    }

    T_q qry(int lo, int hi, int lo_ind, int hi_ind, int ind) {
        if(lo <= lo_ind && hi_ind <= hi) {
            return seg[ind];
        }
        int mid = (lo_ind + hi_ind) >> 1;
        if(lazy[ind] != B::e_u) {
            push(ind, lo_ind, hi_ind);
        }
        T_q op1 = (lo <= mid ? qry(lo, hi, lo_ind, mid, 2 * ind + 1) : B::e_q);
        T_q op2 = (mid < hi ? qry(lo, hi, mid + 1, hi_ind, 2 * ind + 2) : B::e_q);
        return B::comb(op1, op2);
    }

    T_q qry(int lo, int hi) {
        return qry(lo, hi, 0, n - 1, 0);
    }

    void upd(int lo, int hi, T_u delta, int lo_ind, int hi_ind, int ind) {
        if(lo <= lo_ind && hi_ind <= hi) {
            app(ind, lo_ind, hi_ind, delta);
            return;
        }
        int mid = (lo_ind + hi_ind) >> 1;
        if(lazy[ind] != B::e_u) {
            push(ind, lo_ind, hi_ind);
        }
        if(lo <= mid) {
            upd(lo, hi, delta, lo_ind, mid, 2 * ind + 1);
        }
        if(mid < hi) {
            upd(lo, hi, delta, mid + 1, hi_ind, 2 * ind + 2);
        }
        seg[ind] = B::comb(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void upd(int lo, int hi, T_u delta) {
        if(hi < lo) {
            return;
        }
        return upd(lo, hi, delta, 0, n - 1, 0);
    }
};

struct Monoid {
    using T_q = array<int, 4>;
    const T_q e_q = {0, 0, 0, 0};

    using T_u = array<array<int, 4>, 4>;
    const T_u e_u = {array<int, 4>{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    T_q comb(T_q a, T_q b) {
        for(int i = 0; i < 4; i++) {
            a[i] += b[i];
            if(a[i] >= mod) {
                a[i] -= mod;
            }
        }
        return a;
    }

    T_q upd(T_q a, T_u b, int l, int r) {
        T_q res;
        res.fill(0);
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                res[i] += (1LL * b[i][j] * a[j]) % mod;
                if(res[i] >= mod) {
                    res[i] -= mod;
                }
            }
        }
        return res;
    }

    T_u comb_upd(T_u a, T_u b) {
        T_u res;
        for(int i = 0; i < 4; i++) {
            res[i].fill(0);
        }
        for(int i = 0; i < 4; i++) {
            for(int j = i; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    res[i][j] += (1LL * a[i][k] * b[k][j]) % mod;
                    if(res[i][j] >= mod) {
                        res[i][j] -= mod;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] < 0) {
            a[i] += mod;
        }
    }
    vector<array<int, 3>> mods(m);
    vector<vector<array<int, 4>>> qrs(m + 1);
    vector<int> ans(q, 0);
    vector<array<int, 4>> init(n);
    for(int i = 0; i < n; i++) {
        int sq = (1LL * a[i] * a[i]) % mod;
        init[i] = {sq, sq, a[i], 1};
    }
    LazySegTree<Monoid> lst(init);
    for(int i = 0; i < m; i++) {
        cin >> mods[i][0] >> mods[i][1] >> mods[i][2];
        if(mods[i][2] < 0) {
            mods[i][2] += mod;
        }
    }
    for(int i = 0; i < q; i++) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        if(x > 0) {
            qrs[x - 1].push_back({l - 1, r - 1, mod - 1, i});
        }
        qrs[y].push_back({l - 1, r - 1, 1, i});
    }
    auto upd = [&](int lo, int hi, int delta) {
        array<array<int, 4>, 4> mat;
        int sq = (1LL * delta * delta) % mod, dd = (2 * delta) % mod;
        mat = {array<int, 4>{1, 1, dd, sq}, {0, 1, dd, sq}, {0, 0, 1, delta}, {0, 0, 0, 1}};
        lst.upd(lo, hi, mat);
    };
    for(int i = 0; i <= m; i++) {
        if(i > 0) {
            upd(0, mods[i - 1][0] - 2, 0);
            upd(mods[i - 1][0] - 1, mods[i - 1][1] - 1, mods[i - 1][2]);
            upd(mods[i - 1][1], n - 1, 0);
        }
        for(array<int, 4> q: qrs[i]) {
            ans[q[3]] = (ans[q[3]] + (1LL * q[2] * (lst.qry(q[0], q[1])[0])) % mod) % mod;
        }
    }
    for(int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}