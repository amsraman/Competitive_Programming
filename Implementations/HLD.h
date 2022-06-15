// Still WIP I guess
template<class B>
struct HLD : public B {
    size_t n;
    vector
    vector<vector<int>> graph;

    HLD(vector<vector<int>> & g) : n(g.size()), g(g)

    void dfs_sz(int v = 0) {
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
        in[v] = t++;
        for(int u: g[v]) {
            if(u != par[v]) {
                nxt[u] = (u == g[v][0] ? nxt[v] : u), dfs_hld(u);
            }
        }
        out[v] = t;
    }

    int path_qry(int u, int v) {
        int ret = 0;
        while(nxt[u] != nxt[v]) {
            if(in[u] < in[v]) {
                swap(u, v);
            }
            ret += qry(in[nxt[u]], in[u]);
            u = par[nxt[u]];
        }
        if(in[u] > in[v]) {
            swap(u, v);
        }
        return (u == v ? ret : ret + qry(in[u] + 1, in[v]));
    }

    void path_upd(int u, int v) {
        while(nxt[u] != nxt[v]) {
            if(in[u] < in[v]) {
                swap(u, v);
            }
            upd(in[nxt[u]], in[u], 1);
            u = par[nxt[u]];
        }
        if(in[u] > in[v]) {
            swap(u, v);
        }
        upd(in[u] + 1, in[v], 1);
    }
};