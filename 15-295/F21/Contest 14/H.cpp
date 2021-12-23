#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

template<class B>
struct LazySegTree : public B {
    using T_q = typename B::T_q;
    using T_u = typename B::T_u;

    size_t n;
    vector<T_q> seg;
    vector<T_u> lazy;

    LazySegTree(size_t n): n(n), seg(2 * n, B::e_q), lazy(2 * n, B::e_u) {};

    void push(int ind, int lo, int hi) {
        seg[ind] = B::upd(seg[ind], lazy[ind], lo, hi);
        if(lo != hi) {
            lazy[2 * ind + 1] = B::comb_upd(lazy[2 * ind + 1], lazy[ind]);
            lazy[2 * ind + 2] = B::comb_upd(lazy[2 * ind + 2], lazy[ind]);
        }
        lazy[ind] = B::e_u;
    }

    T_q qry(int lo, int hi, int lo_ind, int hi_ind, int ind) {
        push(ind, lo_ind, hi_ind);
        if(lo > hi_ind || hi < lo_ind) {
            return B::e_q;
        }
        if(lo <= lo_ind && hi_ind <= hi) {
            return seg[ind];
        }
        int mid = (lo_ind + hi_ind) / 2;
        return B::comb(qry(lo, hi, lo_ind, mid, 2 * ind + 1), qry(lo, hi, mid + 1, hi_ind, 2 * ind + 2));
    }

    T_q qry(int lo, int hi) {
        return qry(lo, hi, 0, n - 1, 0);
    }

    void upd(int lo, int hi, T_u delta, int lo_ind, int hi_ind, int ind) {
        push(ind, lo_ind, hi_ind);
        if(lo > hi_ind || hi < lo_ind) {
            return;
        }
        if(lo <= lo_ind && hi_ind <= hi) {
            lazy[ind] = delta;
            push(ind, lo_ind, hi_ind);
            return;
        }
        int mid = (lo_ind + hi_ind) / 2;
        upd(lo, hi, delta, lo_ind, mid, 2 * ind + 1);
        upd(lo, hi, delta, mid + 1, hi_ind, 2 * ind + 2);
        seg[ind] = B::comb(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void upd(int lo, int hi, T_u delta) {
        return upd(lo, hi, delta, 0, n - 1, 0);
    }

    int bs_min(int mn, int lo, int hi, int ind, pair<int, int> cur) {
        if(lo == hi) {
            return lo;
        }
        int mid = (lo + hi) / 2;
        push(2 * ind + 1, lo, mid);
        push(2 * ind + 2, mid + 1, hi);
        if(B::comb(cur, seg[2 * ind + 1]).f > mn) {
            return bs_min(mn, lo, mid, 2 * ind + 1, cur);
        } else {
            return bs_min(mn, mid + 1, hi, 2 * ind + 2, B::comb(cur, seg[2 * ind + 1]));
        }
    }
};

int n, num_vals, val[400000];
set<int> coords;
map<int, int> ind;
vector<pair<bool, array<int, 3>>> qrs;

struct MaxPrefix {
    using T_q = pair<int, int>;
    const T_q e_q = {0, 0};

    using T_u = pair<int, bool>;
    const T_u e_u = {0, 0};

    T_q comb(T_q a, T_q b) {
        return {max(a.f, a.s + b.f), a.s + b.s};
    }

    T_q upd(T_q a, T_u b, int l, int r) {
        if(!b.s) {
            return a;
        }
        return {max(0, b.f * (val[r + 1] - val[l])), b.f * (val[r + 1] - val[l])};
    }

    T_u comb_upd(T_u a, T_u b) {
        if(b.s) {
            return b;
        }
        return a;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    coords.insert(0), coords.insert(n);
    while(true) {
        char type;
        cin >> type;
        if(type == 'E') {
            break;
        } else if(type == 'Q') {
            int h;
            cin >> h;
            qrs.push_back({true, {h, 0, 0}});
        } else {
            int a, b, d;
            cin >> a >> b >> d;
            coords.insert(a - 1), coords.insert(b);
            qrs.push_back({false, {a - 1, b, d}});
        }
    }
    for(int c: coords) {
        ind[c] = num_vals;
        val[num_vals++] = c;
    }
    LazySegTree<MaxPrefix> lst((1 << 19));
    for(pair<bool, array<int, 3>> q: qrs) {
        if(q.f) {
            int ub = lst.bs_min(q.s[0], 0, (1 << 19) - 1, 0, {0, 0});
            if(ub >= num_vals - 1) {
                cout << n << '\n';
                continue;
            }
            // linearly interpolate from (vals[ub], lev1) to (vals[ub + 1], lev2)
            int lev1 = (ub == 0 ? 0 : lst.qry(0, ub - 1).s), lev2 = lst.qry(0, ub).s, grad = (lev2 - lev1) / (val[ub + 1] - val[ub]);
            cout << val[ub] + (q.s[0] - lev1) / grad << '\n';
        } else {
            lst.upd(ind[q.s[0]], ind[q.s[1]] - 1, {q.s[2], true});
        }
    }
}