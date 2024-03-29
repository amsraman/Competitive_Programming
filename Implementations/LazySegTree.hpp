template <class B>
struct LazySegTree : public B {
    using T_q = typename B::T_q;
    using T_u = typename B::T_u;
    int n, sz, log; vector<T_q> seg; vector<T_u> lazy;
    LazySegTree(int n): n(n), log(__lg(max(n - 1, 1)) + 1) {
        sz = (1 << log), seg.resize(sz << 1, B::e_q), lazy.resize(sz << 1, B::e_u);
    }
    LazySegTree(vector<T_q> & init): n((int) init.size()), log(__lg(max(n - 1, 1)) + 1) {
        sz = (1 << log), seg.resize(sz << 1, B::e_q), lazy.resize(sz << 1, B::e_u);
        copy(init.begin(), init.end(), seg.begin() + sz);
        for(int i = sz - 1; i > 0; i--) refresh(i);
    }
    void refresh(int ind) {
        seg[ind] = B::comb(seg[2 * ind], seg[2 * ind + 1]);
    }
    void app(int ind, int lo, int hi, T_u delta) {
        seg[ind] = B::upd(seg[ind], delta, lo, hi);
        lazy[ind] = B::comb_upd(delta, lazy[ind]);
    }
    void push(int ind, int lo, int hi) {
        if(lo != hi) {
            int mid = (lo + hi) >> 1;
            app(2 * ind, lo, mid, lazy[ind]);
            app(2 * ind + 1, mid + 1, hi, lazy[ind]);
        }
        lazy[ind] = B::e_u;
    }
    void push_from_root(int ind) {
        ind += sz;
        for(int i = log; i > 0; i--) {
            push(ind >> i, (ind >> i << i) - sz, (((ind >> i) + 1) << i) - sz - 1);
        }
    }
    T_q qry(int lo, int hi) {
        push_from_root(lo), push_from_root(hi); T_q ret1 = B::e_q, ret2 = B::e_q;
        for(lo += sz, hi += sz; lo <= hi; lo >>= 1, hi >>= 1) {
            if(lo & 1) ret1 = B::comb(ret1, seg[lo++]);
            if(hi & 1 ^ 1) ret2 = B::comb(seg[hi--], ret2);
        }
        return B::comb(ret1, ret2);
    }
    void upd(int lo, int hi, T_u delta) {
        push_from_root(lo), push_from_root(hi); lo += sz, hi += sz;
        for(int l = lo, r = hi, lvl = 0; l <= r; l >>= 1, r >>= 1, ++lvl) {
            if(l & 1) app(l, (l << lvl) - sz, (l + 1 << lvl) - sz - 1, delta), l++;
            if(r & 1 ^ 1) app(r, (r << lvl) - sz, (r + 1 << lvl) - sz - 1, delta), r--;
        }
        for(int i = 1; i <= log; i++) {
            if(lo >> i << i != lo) refresh(lo >> i);
            if((hi + 1) >> i << i != hi + 1) refresh(hi >> i);
        }
    }
};

struct MaxInt {
    using T_q = int; const T_q e_q = 0;
    using T_u = int; const T_u e_u = 0;
    T_q comb(T_q a, T_q b) {
        return max(a, b);
    }
    T_q upd(T_q a, T_u b, int l, int r) {
        return a + b;
    }
    T_u comb_upd(T_u a, T_u b) {
        // a after b
        return a + b;
    }
};