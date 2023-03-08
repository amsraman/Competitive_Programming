template <int log = 20>
struct BinaryLifter {
    int n, root;
    vector<int> dep;
    vector<vector<int>> graph;
    vector<array<int, log + 1>> par;
    BinaryLifter(const vector<vector<int>> & graph, int root = 0): n((int) graph.size()), root(root), graph(graph) {
        dep.resize(n, 0), par.resize(n);
        dfs(root, root);
        for(int i = 0; i < log; i++) {
            for(int j = 0; j < n; j++) {
                par[j][i + 1] = par[par[j][i]][i];
            }
        }
    }
    void dfs(int u, int p) {
        par[u].fill(root); par[u][0] = p;
        for(int v: graph[u]) {
            if(v != p) {
                dep[v] = dep[u] + 1;
                dfs(v, u);
            }
        }
    }
    int kth_ancestor(int u, int k) {
        if(k > dep[u]) return -1;
        for(int i = 0; i <= log; i++) {
            if((k >> i) & 1) {
                u = par[u][i];
            }
        }
        return u;
    }
    int lca(int u, int v) {
        if(dep[u] < dep[v]) swap(u, v);
        for(int i = log; i >= 0; i--) {
            if(((dep[u] - dep[v]) >> i) & 1) {
                u = par[u][i];
            }
        }
        for(int i = log; i >= 0; i--) {
            if(par[u][i] != par[v][i]) {
                u = par[u][i], v = par[v][i];
            }
        }
        return (u == v ? u : par[u][0]);
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};