#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int n; vector<int> link, sz;
    DSU(int n): n(n), link(n), sz(n, 1) {
        iota(link.begin(), link.end(), 0);
    }
    int find(int x) {
        return (x == link[x] ? x : link[x] = find(link[x]));
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x;
    }
};

template <bool EDGE_VALS = true>
struct HLD {
    int n, t = 0;
    vector<int> sz, par, nxt, in, out;
    vector<vector<int>> graph;
    HLD(vector<vector<int>> & graph) : n((int) graph.size()), graph(graph), sz(n, -1), par(n), nxt(n), in(n), out(n) {
        for(int i = 0; i < n; i++) {
            if(sz[i] == -1) {
                nxt[i] = par[i] = i;
                dfs_sz(i), dfs_hld(i);
            }
        }
    }
    void dfs_sz(int v) { // generates sz and par, places heavy child first
        sz[v] = 1;
        for(int & u: graph[v]) {
            if(u == par[v]) continue;
            par[u] = v, dfs_sz(u), sz[v] += sz[u];
            if(sz[u] > sz[graph[v][0]]) swap(u, graph[v][0]);
        }
    }
    void dfs_hld(int v) { // generate preorder traversal, heavy chains
        in[v] = t++;
        for(int u: graph[v]) {
            if(u != par[v]) {
                nxt[u] = (u == graph[v][0] ? nxt[v] : u), dfs_hld(u);
            }
        }
        out[v] = t;
    }
    void process_path(int u, int v, function<void (int, int)> f) {
        while(nxt[u] != nxt[v]) {
            if(in[u] < in[v]) swap(u, v);
            f(in[nxt[u]], in[u]);
            u = par[nxt[u]];
        }
        if(u == v && EDGE_VALS) return;
        if(in[u] > in[v]) swap(u, v);
        f(in[u] + EDGE_VALS, in[v]); // exclude root if we have edge values
    }
    void process_subtree(int u, function<void (int, int)> f) {
        if(sz[u] == 1 && EDGE_VALS) return;
        f(in[u], out[u]);
    }
};

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
    int n, m, q; cin >> n >> m >> q;
    vector<tuple<int, int, int>> edges; vector<bool> used(m, false);
    vector<vector<int>> mst(n);
    for(int i = 0, u, v, t; i < m; i++) {
        cin >> u >> v >> t; --u, --v;
        edges.emplace_back(t, u, v);
    }
    sort(edges.begin(), edges.end());
    DSU d(n);
    for(int i = 0; i < m; i++) {
        auto [w, u, v] = edges[i];
        if(d.find(u) != d.find(v)) {
            d.unite(u, v); used[i] = true;
            mst[u].push_back(v); mst[v].push_back(u);
        }
    }
    HLD hld(mst); SegTree<MaxInt> st(n);
    auto path_upd = [&](int u, int v, int delta) {
        auto f = [&](int i, int j) {
            assert(i == j);
            st.upd(i, delta);
        };
        hld.process_path(u, v, f);
    };
    auto path_qry = [&](int u, int v) {
        int res = 0;
        auto f = [&](int i, int j) {
            res = max(res, st.qry(i, j));
        };
        hld.process_path(u, v, f);
        return res;
    };
    for(int i = 0; i < m; i++) {
        if(used[i]) {
            auto [w, u, v] = edges[i];
            path_upd(u, v, w);
        }
    }
    vector<int> ans1(q), ans2(q);
    vector<tuple<int, int, int>> pending;
    for(int i = 0, a, b; i < q; i++) {
        cin >> a >> b; --a, --b;
        ans1[i] = path_qry(a, b);
        pending.emplace_back(ans1[i], a, i);
    }
    sort(pending.begin(), pending.end());
    DSU d2(n);
    for(int i = 0, j = 0; i < m; i++) {
        auto [w, u, v] = edges[i];
        if(d2.find(u) == d2.find(v)) continue;
        while(j < q && get<0>(pending[j]) < w) {
            auto [_, st, ind] = pending[j];
            ans2[ind] = d2.sz[d2.find(st)];
            ++j;
        }
        d2.unite(u, v);
    }
    for(int i = 0; i < q; i++) {
        cout << ans1[i] << " " << (ans2[i] == 0 ? n : ans2[i]) << '\n';
    }
}