#include <bits/stdc++.h>

using namespace std;

template <class B>
struct SegTree : public B {
    using T = typename B::T;
    int n, sz, log; vector<T> seg;
    SegTree(int n): n(n), log(__lg(max(n - 1, 1)) + 1) {
        sz = (1 << log), seg.resize(sz << 1, B::e);
    };
    SegTree(vector<T> & init): n((int) init.size()), log(__lg(max(n - 1, 1)) + 1) {
        sz = (1 << log), seg.resize(sz << 1, B::e);
        copy(init.begin(), init.end(), seg.begin() + sz);
        for(int i = sz - 1; i > 0; i--) refresh(i);
    };
    void refresh(int ind) {
        seg[ind] = B::comb(seg[2 * ind], seg[2 * ind + 1]);
    }
    T qry(int lo, int hi) {
        T ret1 = B::e, ret2 = B::e;
        for(lo += sz, hi += sz; lo <= hi; lo >>= 1, hi >>= 1) {
            if(lo & 1) ret1 = B::comb(ret1, seg[lo++]);
            if(hi & 1 ^ 1) ret2 = B::comb(seg[hi--], ret2);
        }
        return B::comb(ret1, ret2);
    }
    void upd(int ind, T val) {
        seg[ind += sz] = val;
        while(ind > 1) {
            ind >>= 1; refresh(ind);
        }
    }
};

struct MaxInt {
    using T = int;
    const T e = 0;
    T comb(T a, T b) {
        return max(a, b);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> a(n), ia(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i]; --a[i];
        ia[a[i]] = i;
    }
    SegTree<MaxInt> st(a);
    vector<int> lc(n, -1), rc(n, -1), in(n), out(n), sz(n, 0), dep(n, 0); int tm = 0;
    vector<vector<int>> par(n, vector<int>(17));
    auto dfs = [&](auto rec, int l, int r, int d = 0) -> int {
        int mid = ia[st.qry(l, r)];
        in[mid] = tm++; sz[mid] = 1; dep[mid] = d;
        if(l < mid) {
            lc[mid] = rec(rec, l, mid - 1, d + 1);
            par[lc[mid]][0] = mid;
            sz[mid] += sz[lc[mid]];
        }
        if(mid < r) {
            rc[mid] = rec(rec, mid + 1, r, d + 1);
            par[rc[mid]][0] = mid;
            sz[mid] += sz[rc[mid]];
        }
        out[mid] = tm - 1;
        return mid;
    };
    int root = dfs(dfs, 0, n - 1);
    par[root][0] = root;
    for(int j = 1; j < 17; j++) {
        for(int i = 0; i < n; i++) {
            par[i][j] = par[par[i][j - 1]][j - 1];
        }
    }
    auto is_anc = [&](int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    };
    auto get_sz = [&](int u) {
        if(u == -1) return 0;
        return sz[u];
    };
    auto lca = [&](int u, int v) {
        if(dep[u] < dep[v]) swap(u, v);
        for(int j = 16; j >= 0; j--) {
            if(((dep[u] - dep[v]) >> j) & 1) {
                u = par[u][j];
            }
        }
        for(int j = 16; j >= 0; j--) {
            if(par[u][j] != par[v][j]) {
                u = par[u][j], v = par[v][j];
            }
        }
        return u == v ? u : par[u][0];
    };
    auto anc_at_k = [&](int u, int anc, int k) {
        if(u == anc) return k == 1;
        if(u < anc) {
            int my_mx = st.qry(u, anc - 1);
            int lb = anc + 1, ub = n;
            while(lb < ub) {
                int mid = (lb + ub) / 2;
                if(st.qry(anc + 1, mid) > my_mx) {
                    ub = mid;
                } else {
                    lb = mid + 1;
                }
            }
            return ub - u == k;
        } else {
            int my_mx = st.qry(anc + 1, u);
            int lb = -1, ub = anc - 1;
            while(lb < ub) {
                int mid = (lb + ub + 1) / 2;
                if(st.qry(mid, anc - 1) > my_mx) {
                    lb = mid;
                } else {
                    ub = mid - 1;
                }
            }
            return u - ub == k;
        }
    };
    vector<int> res(q, 0); vector<vector<pair<int, int>>> at_p(n);
    for(int i = 0, p, k; i < q; i++) {
        cin >> p >> k; --p;
        if(p - k == -1 || (p >= k && is_anc(p - k, p))) {
            res[i] += get_sz(lc[lca(p - k + 1, p)]);
        }
        if(p + k == n || (p + k < n && is_anc(p + k, p))) {
            res[i] += get_sz(rc[lca(p + k - 1, p)]);
        }
        at_p[p].emplace_back(k, i);
        // res += anc_at_k(p, anc, k);
    }
    set<int> cur;
    auto dfs2 = [&](auto rec, int u) -> void {
        cur.insert(u);
        for(auto [k, ind]: at_p[u]) {
            auto it = cur.lower_bound(u - k + 1);
            if(it != cur.end() && *it < u) res[ind] += (int) anc_at_k(u, *it, k);
            it = cur.upper_bound(u + k - 1);
            if(it != cur.begin() && *prev(it) >= u) res[ind] += (int) anc_at_k(u, *prev(it), k);
        }
        if(lc[u] != -1) rec(rec, lc[u]);
        if(rc[u] != -1) rec(rec, rc[u]);
        cur.erase(u);
    };
    dfs2(dfs2, root);
    for(int i = 0; i < q; i++) {
        cout << res[i] << '\n';
    }
}
/*
consider node k in the cartesian tree:
- I am only picked if:
    - I come from the right, and my entire left subtree is complete
        - If I started within this subtree, then yeah this is just what it is
        - If I started from OUTSIDE this subtree... that means that still my entire subtree must've been completed
            - But it also means that we're sort of playing ping pong with another subtree. 
*/