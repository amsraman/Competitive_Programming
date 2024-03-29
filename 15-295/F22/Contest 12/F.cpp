#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

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
        bld(init, 0, n - 1, 0);
    }
    void bld(const vector<T_q> & init, int lo, int hi, int ind) {
        if(lo == hi) {
            seg[ind] = init[lo];
            return;
        }
        int mid = (lo + hi) >> 1;
        bld(init, lo, mid, 2 * ind + 1), bld(init, mid + 1, hi, 2 * ind + 2);
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
        if(lazy[ind] != B::e_u) push(ind, lo_ind, hi_ind);
        T_q op1 = (lo <= mid ? qry(lo, hi, lo_ind, mid, 2 * ind + 1) : B::e_q);
        T_q op2 = (mid < hi ? qry(lo, hi, mid + 1, hi_ind, 2 * ind + 2) : B::e_q);
        return B::comb(op1, op2);
    }
    void upd(int lo, int hi, T_u delta, int lo_ind, int hi_ind, int ind) {
        if(lo <= lo_ind && hi_ind <= hi) {
            app(ind, lo_ind, hi_ind, delta);
            return;
        }
        int mid = (lo_ind + hi_ind) >> 1;
        if(lazy[ind] != B::e_u) push(ind, lo_ind, hi_ind);
        if(lo <= mid) upd(lo, hi, delta, lo_ind, mid, 2 * ind + 1);
        if(mid < hi) upd(lo, hi, delta, mid + 1, hi_ind, 2 * ind + 2);
        seg[ind] = B::comb(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    T_q qry(int lo, int hi) {
        return qry(lo, hi, 0, n - 1, 0);
    }
    void upd(int lo, int hi, T_u delta) {
        upd(lo, hi, delta, 0, n - 1, 0);
    }
};

struct MinInt {
    using T_q = int; const T_q e_q = 0x3f3f3f3f;
    using T_u = int; const T_u e_u = 0;
    T_q comb(T_q a, T_q b) {
        return min(a, b);
    }
    T_q upd(T_q a, T_u b, int l, int r) {
        return a + b;
    }
    T_u comb_upd(T_u a, T_u b) {
        // a after b
        return a + b;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> h(n), l(n);
    for(int i = 0; i < n; i++) {
        cin >> h[i] >> l[i];
    }
    vector<int> dp(n + 1, 0);
    LazySegTree<MinInt> lst(dp);
    stack<pair<int, int>> top_stack, bottom_stack;
    map<int, int> top_lst, bottom_lst;
    top_stack.push({0, 0}); bottom_stack.push({0, 0});
    for(int i = 0; i < n; i++) {
        while(top_stack.top().f >= h[i]) top_stack.pop();
        while(bottom_stack.top().f >= l[i]) bottom_stack.pop();
        pair<int, int> tp1 = top_stack.top(), tp2 = bottom_stack.top();
        if(top_lst.count(h[i]) && top_lst[h[i]] > tp1.s) {
            lst.upd(top_lst[h[i]], i, 1);
        } else if(i > 0) {
            lst.upd(0, i, 1);
        }
        if(bottom_lst.count(l[i]) && bottom_lst[l[i]] > tp2.s) {
            lst.upd(bottom_lst[l[i]], i, 1);
        } else if(i > 0) {
            lst.upd(0, i, 1);
        }
        top_stack.push({h[i], i + 1}); bottom_stack.push({l[i], i + 1});
        dp[i + 1] = lst.qry(0, i) + 1; lst.upd(i + 1, i + 1, dp[i + 1] - 2);
        top_lst[h[i]] = bottom_lst[l[i]] = i + 1;
    }
    cout << dp[n] - 1 << '\n';
}