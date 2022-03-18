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

// Sample MixIn

struct MaxInt {
    using T_q = int;
    const T_q e_q = 0;

    using T_u = int;
    const T_u e_u = 0;

    T_q comb(T_q a, T_q b) {
        return (a > b ? a : b);
    }

    T_q upd(T_q a, T_u b, int l, int r) {
        return a + b;
    }

    T_u comb_upd(T_u a, T_u b) {
        return a + b;
    }
};