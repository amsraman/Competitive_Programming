#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

struct BridgeTree {
    int n, time = 0, comp_count = 0;
    vector<int> lp, comp;
    vector<vector<int>> graph, bridge_tree, comps;
    stack<int> dfs_stack;
    vector<pair<int, int>> bridge_list;
    void dfs(int u, int p = -1) {
        int low = lp[u] = time++, v;
        bool par_found = false;
        dfs_stack.push(u);
        for(int v: graph[u]) {
            if(lp[v] == -1) dfs(v, u);
            if(v == p && !par_found) {
                par_found = true;
            } else {
                low = min(low, lp[v]);
            }
        }
        if(p == -1 || low == lp[u]) {
            if(p != -1) bridge_list.emplace_back(p, u);
            comps.emplace_back();
            do {
                v = dfs_stack.top(); dfs_stack.pop();
                comp[v] = comp_count, comps[comp_count].push_back(v);
            } while(v != u);
            comp_count++;
        }
        lp[u] = low;
    }
    BridgeTree(const vector<vector<int>> & graph): n((int) graph.size()), graph(graph), lp(n, -1), comp(n) {
        for(int i = 0; i < n; i++) {
            if(lp[i] == -1) dfs(i);
        }
        bridge_tree.resize(comp_count);
        for(auto [u, v]: bridge_list) {
            bridge_tree[comp[u]].push_back(comp[v]);
            bridge_tree[comp[v]].push_back(comp[u]);
        }
    }
};

template <bool EDGE_VALS = false>
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
struct SparseTable : public B {
    using T = typename B::T;
    int n; vector<vector<T>> st;
    SparseTable(vector<T> & a): n((int) a.size()), st(__lg(n) + 1, vector<T>(n, B::e)) {
        for(int i = 0; i < n; i++) {
            st[0][i] = a[i];
        }
        int lev = __lg(n);
        for(int i = 1; i <= lev; i++) {
            for(int j = 0; j < n; j++) {
                st[i][j] = B::comb(st[i - 1][j], st[i - 1][min(n - 1, j + (1 << (i - 1)))]);
            }
        }
    }
    T qry(int l, int r) {
        int lev = __lg(r - l + 1);
        return B::comb(st[lev][l], st[lev][r - (1 << lev) + 1]);
    }
};

struct Band {
    using T = int;
    const T e = INT_MAX;
    T comb(T a, T b) {
        return min(a, b);
    }
};

int main() {
    ifstream cin("road_to_nutella_input.txt");
    ofstream cout("output.txt");
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m; cin >> n >> m;
        vector<vector<int>> g(n);
        for(int i = 0, u, v; i < m; i++) {
            cin >> u >> v; --u, --v;
            g[u].push_back(v); g[v].push_back(u);
        }
        BridgeTree bt(g);
        auto bridge_tree = bt.bridge_tree;
        int sz = bt.comp_count;
        vector<bool> in(n, false), bip(sz);
        vector<int> col(n, -1), dist(sz, 1e9);
        bool cur_bip = true;
        auto dfs = [&](auto rec, int u) -> void {
            for(int v: g[u]) {
                if(!in[v]) continue;
                if(col[v] == -1) {
                    col[v] = col[u] ^ 1;
                    rec(rec, v);
                } else if(col[v] == col[u]) {
                    cur_bip = false;
                }
            }
        };
        HLD hld(bridge_tree);
        queue<int> qu;
        for(int i = 0; i < sz; i++) {
            for(int v: bt.comps[i]) in[v] = true;
            col[bt.comps[i][0]] = 0;
            dfs(dfs, bt.comps[i][0]);
            bip[i] = cur_bip, cur_bip = true;
            for(int v: bt.comps[i]) in[v] = false;
            if(!bip[i]) {
                qu.push(i);
                dist[hld.in[i]] = 0;
            }
        }
        while(!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(int v: bridge_tree[u]) {
                if(dist[hld.in[v]] == 1e9) {
                    qu.push(v);
                    dist[hld.in[v]] = dist[hld.in[u]] + 1;
                }
            }
        }
        ll ans = 0;
        SparseTable<Band> st(dist);
        auto qry = [&](int u, int v) {
            int res = 1e9;
            auto proc = [&](int i, int j) {
                res = min(res, st.qry(i, j));
            };
            hld.process_path(u, v, proc);
            return res;
        };
        int q; cin >> q;
        for(int i = 0, a, b; i < q; i++) {
            cin >> a >> b;
            a = bt.comp[a - 1], b = bt.comp[b - 1];
            int res = qry(a, b);
            if(res == 1e9) res = -1;
            ans += res;
        }
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}