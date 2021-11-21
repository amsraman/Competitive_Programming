#include <bits/stdc++.h>
typedef long long ll;
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
        if(lazy[ind] > 0) {
            push(ind, lo_ind, hi_ind);
        }
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
        if(lazy[ind] > 0) {
            push(ind, lo_ind, hi_ind);
        }
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

    // Find the minimum index whose prefix is > sum and subtract one
    int bs_sum(ll sum, int lo, int hi, int ind) {
        if(lo == hi) {
            return (seg[ind].f > sum ? lo - 1 : lo);
        }
        int mid = (lo + hi) / 2;
        if(lazy[2 * ind + 1] > 0) {
            push(2 * ind + 1, lo, mid);
        }
        if(lazy[2 * ind + 2] > 0) {
            push(2 * ind + 2, mid + 1, hi);
        }
        if(seg[2 * ind + 1].f > sum) {
            return bs_sum(sum, lo, mid, 2 * ind + 1);
        } else {
            return bs_sum(sum - seg[2 * ind + 1].f, mid + 1, hi, 2 * ind + 2);
        }
    }

    // Find the minimum index whose value is <= mn (n if none are)
    int bs_min(int mn, int lo, int hi, int ind) {
        if(lo == hi) {
            return (seg[ind].s <= mn ? lo : lo + 1);
        }
        int mid = (lo + hi) / 2;
        if(lazy[2 * ind + 1] > 0) {
            push(2 * ind + 1, lo, mid);
        }
        if(lazy[2 * ind + 2] > 0) {
            push(2 * ind + 2, mid + 1, hi);
        }
        if(seg[2 * ind + 1].s <= mn) {
            return bs_min(mn, lo, mid, 2 * ind + 1);
        } else {
            return bs_min(mn, mid + 1, hi, 2 * ind + 2);
        }
    }
};

struct SumMaxAssignPII {
    using T_q = pair<ll, int>;
    const T_q e_q = {0, 0x3f3f3f3f};

    using T_u = int;
    const T_u e_u = 0;

    T_q comb(T_q a, T_q b) {
        return {a.f + b.f, min(a.s, b.s)};
    }

    T_q upd(T_q a, T_u b, int l, int r) {
        if(b == 0) {
            return a;
        }
        return {(ll) (r - l + 1) * b, b};
    }

    T_u comb_upd(T_u a, T_u b) {
        return (b == 0 ? a : b);
    }
};

int n, q, a[200000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    LazySegTree<SumMaxAssignPII> st((1 << 18));
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        st.upd(i, i, a[i]);
    }
    for(int i = 0, t, x, y; i < q; i++) {
        cin >> t >> x >> y;
        if(t == 1) {
            int ind = st.bs_min(y, 0, (1 << 18) - 1, 0);
            if(ind <= x - 1) {
                st.upd(ind, x - 1, y);
            }
        } else {
            int ans = 0;
            x = max(x - 1, st.bs_min(y, 0, (1 << 18) - 1, 0));
            while(x < n) {
                int nxt_end = min(n - 1, st.bs_sum(st.qry(0, x - 1).f + y, 0, (1 << 18) - 1, 0));
                y -= st.qry(x, nxt_end).f;
                ans += (nxt_end - x + 1);
                x = max(nxt_end + 1, st.bs_min(y, 0, (1 << 18) - 1, 0));
            }
            cout << ans << '\n';
        }
    }
}
// hey... this isn't the custom invocation window!!!11!!11one!!111