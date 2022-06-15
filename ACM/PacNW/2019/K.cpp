#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

template<typename T>
struct FenwickTree {
    size_t n;
    vector<T> bit;

    FenwickTree(size_t n): n(n), bit(n, 0) {};

    FenwickTree(int n, vector<T> & init): n(n), bit(n) {
        copy(init.begin(), init.end(), bit.begin());
        for(int i = 1; i <= n; i++) {
            if(i + (i & -i) <= n) {
                bit[i + (i & -i) - 1] += bit[i - 1];
            }
        }
    }

    T qry(int k) {
        T ret = 0;
        for(k++; k > 0; k -= (k & -k)) {
            ret += bit[k - 1];
        } 
        return ret;
    }

    T range_qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }

    void upd(int k, T x) {
        for(k++; k <= n; k += (k & -k)) {
            bit[k - 1] += x;
        }
    }
};

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

struct Info {
    using T_q = array<int, 3>;
    const T_q e_q = {-1, -1, -1};

    using T_u = array<int, 3>;
    const T_u e_u = {-1, -1, -1};

    T_q comb(T_q a, T_q b) {
        return (a == e_q ? b : a);
    }

    T_q upd(T_q a, T_u b, int l, int r) {
        return b;
    }

    T_u comb_upd(T_u a, T_u b) {
        return a;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> sizes(n), ans(q, -1), rec(q, -1);
    vector<FenwickTree<int>> ft;
    for(int i = 0, sz; i < m; i++) {
        cin >> sz;
        vector<int> x(sz);
        for(int j = 0; j < sz; j++) {
            cin >> x[j];
        }
        for(int j = sz - 1; j > 0; j--) {
            x[j] -= x[j - 1];
        }
        ft.push_back(FenwickTree<int>(sz, x)), sizes[i] = sz;
    }
    LazySegTree<Info> lst(1 << 19);
    vector<array<int, 3>> incr(q, {-1, -1, -1});
    vector<vector<pair<int, int>>> ord(q);
    for(int i = 0, t; i < q; i++) {
        cin >> t;
        if(t == 1) {
            int ind, p;
            cin >> ind >> p;
            lst.upd(p - 1, p + sizes[ind - 1] - 2, {ind - 1, p - 1, rec[ind - 1]});
        } else if(t == 2) {
            int p;
            cin >> p;
            array<int, 3> ev = lst.qry(p - 1, p - 1);
            if(ev[2] >= 0) {
                ord[ev[2]].push_back({p - ev[1] - 1, i});
            } else if(ev[0] >= 0) {
                ans[i] = ft[ev[0]].qry(p - ev[1] - 1);
            } else {
                ans[i] = 0;
            }
        } else {
            int ind, l, r;
            cin >> ind >> l >> r;
            incr[i] = {ind - 1, l - 1, r - 1}, rec[ind - 1] = i;
        }
    }
    for(int i = 0; i < q; i++) {
        if(incr[i][0] > -1) {
            ft[incr[i][0]].upd(incr[i][1], 1);
            if(incr[i][2] < n - 1) {
                ft[incr[i][0]].upd(incr[i][2] + 1, -1);
            }
            for(pair<int, int> o: ord[i]) {
                ans[o.s] = ft[incr[i][0]].qry(o.f);
            }
        }
    }
    for(int a: ans) {
        if(a >= 0) {
            cout << a % 256 << '\n';
        }
    }
}