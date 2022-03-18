#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

template<class B>
struct LazySegTree : public B {
    using T_q = typename B::T_q;
    using T_u = typename B::T_u;

    size_t n;
    vector<T_q> seg;
    vector<T_u> lazy;

    LazySegTree(size_t n): n(n), seg(2 * n, B::e_q), lazy(2 * n, B::e_u) {};

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
        return upd(lo, hi, delta, 0, n - 1, 0);
    }
};

int n, k, ncr[11][11];
vector<pair<int, int>> intervals;

int add(int x, int y) {
    if(x + y >= mod) {
        return x + y - mod;
    }
    return x + y;
}

struct SegInfo {
    using T_q = array<int, 11>;
    const T_q e_q = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    using T_u = array<int, 11>;
    // This is really hacky but negative = multiply, non-negative = assignment
    const T_u e_u = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    T_q comb(T_q a, T_q b) {
        for(int i = 0; i < 11; i++) {
            a[i] = add(a[i], b[i]);
        }
        return a;
    }

    T_q upd(T_q a, T_u b, int l, int r) {
        if(b[0] < 0) {
            for(int i = 0; i < 11; i++) {
                a[i] = (1LL * a[i] * -b[i]) % mod;
            }
            return a;
        }
        return b;
    }

    T_u comb_upd(T_u a, T_u b) {
        if(a[0] >= 0) {
            return a;
        } else if(b[0] < 0) {
            for(int i = 0; i < 11; i++) {
                a[i] = -((1LL * a[i] * b[i]) % mod);
            }
            return a;
        }
        for(int i = 0; i < 11; i++) {
            a[i] = (1LL * -a[i] * b[i]) % mod;
        }
        return a;
    }
};

int main() {
    ifstream cin("help.in");
    ofstream cout("help.out");
    cin >> n >> k;
    intervals.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> intervals[i].f >> intervals[i].s;
    }
    sort(intervals.begin(), intervals.end());
    ncr[0][0] = 1;
    for(int i = 1; i <= k; i++) {
        ncr[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            ncr[i][j] = add(ncr[i - 1][j - 1], ncr[i - 1][j]);
        }
    }
    LazySegTree<SegInfo> dp((1 << 18));
    array<int, 11> init, double_msk;
    init.fill(0), init[0] = 1;
    double_msk.fill(-2);
    dp.upd(0, 0, init);
    for(pair<int, int> i: intervals) {
        array<int, 11> t1 = dp.qry(0, i.f - 1), t2 = dp.qry(i.f, i.s - 1), nxt;
        for(int j = 0; j <= k; j++) {
            int tot = 0;
            for(int pv = 0; pv <= j; pv++) {
                int cur = (1LL * t1[pv] * ncr[j][pv]) % mod;
                tot = add(tot, cur);
            }
            tot = add(tot, t2[j]);
            nxt[j] = tot;
        }
        dp.upd(i.s, i.s, nxt);
        dp.upd(i.s + 1, 2 * n, double_msk);
    }
    cout << dp.qry(0, 2 * n)[k] << endl;
}
