#include <bits/stdc++.h>

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
};

// Sample MixIn

struct SumInt {
    using T_q = int;
    const T_q e_q = 0;

    using T_u = int;
    const T_u e_u = 0;

    T_q comb(T_q a, T_q b) {
        return a + b;
    }

    T_q upd(T_q a, T_u b, int l, int r) {
        return a + b * (r - l + 1);
    }

    T_u comb_upd(T_u a, T_u b) {
        return a + b;
    }
};

int t, n, f[800000], ans, sz[800000], par[800000], nxt[800000], ct, in[800000], out[800000];
vector<int> g[800000], frq[800000];
LazySegTree<SumInt> lst((1 << 20));

void dfs_sz(int v = 0)  {
    sz[v] = 1;
    for(int &u: g[v]) {
        if(u == par[v]) {
            continue;
        }
        par[u] = v, dfs_sz(u), sz[v] += sz[u];
        if(sz[u] > sz[g[v][0]]) {
            swap(u, g[v][0]);
        }
    }
}

void dfs_hld(int v = 0) {
    in[v] = ct++;
    for(int u: g[v]) {
        if(u != par[v]) {
            nxt[u] = (u == g[v][0] ? nxt[v] : u);
            dfs_hld(u);
        }
    }
    out[v] = ct;
}

int path_qry(int u, int v) {
    int ret = 0;
    while(nxt[u] != nxt[v]) {
        if(in[u] < in[v]) {
            swap(u, v);
        }
        ret += lst.qry(in[nxt[u]], in[u]);
        u = par[nxt[u]];
    }
    if(in[u] > in[v]) {
        swap(u, v);
    }
    return (u == v ? ret : ret + lst.qry(in[u] + 1, in[v]));
}

void path_upd(int u, int v) {
    while(nxt[u] != nxt[v]) {
        if(in[u] < in[v]) {
            swap(u, v);
        }
        lst.upd(in[nxt[u]], in[u], -1);
        u = par[nxt[u]];
    }
    if(in[u] > in[v]) {
        swap(u, v);
    }
    lst.upd(in[u] + 1, in[v], -1);
}

int main() {
    freopen("chainblock_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        for(int i = 0; i < n; i++) {
            cin >> f[i];
            frq[f[i] - 1].push_back(i);
        }
        lst.upd(0, n - 1, 1);
        ct = 0, dfs_sz(0), dfs_hld(0);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < (int) frq[i].size() - 1; j++) {
                path_upd(frq[i][j], frq[i][j + 1]);
            }
        }
        int ans = 0;
        for(int i = 1; i < n; i++) {
            ans += (path_qry(i, par[i]) > 0);
        }
        cout << "Case #" << _ << ": " << ans << endl;
        for(int i = 0; i < n; i++) {
            g[i].clear();
            frq[i].clear();
        }
        for(int i = 0; i < (1 << 21); i++) {
            lst.seg[i] = lst.lazy[i] = 0;
        }
    }
}