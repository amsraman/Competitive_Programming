template <bool EDGE_VALS>
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