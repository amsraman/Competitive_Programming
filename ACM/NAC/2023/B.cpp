#include <bits/stdc++.h>

using namespace std;

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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q, tm = 0; cin >> n >> q;
    vector<vector<int>> g(n), tree(n);
    for(int i = 0, u, v; i < n + 1; i++) {
        cin >> u >> v; --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    vector<int> in(n, -1), out(n), par(n), mem_cyc(n, 0);
    vector<pair<int, int>> extra_edge;
    auto dfs = [&](auto rec, int u, int p) -> void {
        in[u] = tm++, par[u] = p;
        for(int v: g[u]) {
            if(in[v] == -1) {
                rec(rec, v, u);
                tree[u].push_back(v), tree[v].push_back(u);
            } else if(v != p && u < v) {
                extra_edge.emplace_back(u, v);
            }
        }
        out[u] = tm++;
    };
    auto dfs2 = [&](auto rec, int u, int p) -> void {
        for(int v: tree[u]) {
            if(v != p && mem_cyc[v] == 0) {
                mem_cyc[v] = mem_cyc[u];
                rec(rec, v, u);
            }
        }
    };
    dfs(dfs, 0, 0);
    BinaryLifter bl(tree);
    auto is_anc = [&](int u, int v) { // is u an ancestor of v
        return in[u] <= in[v] && out[v] <= out[u];
    };
    auto line_intersect = [&](pair<int, int> l1, pair<int, int> l2) {
        if(is_anc(l2.first, l1.first)) swap(l1, l2);
        int l = bl.lca(l1.second, l2.second);
        return is_anc(l1.first, l2.first) && is_anc(l2.first, l) && l2.first != l;
    };
    auto path_intersect = [&](pair<int, int> p1, pair<int, int> p2) {
        int l1 = bl.lca(p1.first, p1.second), l2 = bl.lca(p2.first, p2.second);
        pair<int, int> p11 = {l1, p1.first}, p12 = {l1, p1.second}, p21 = {l2, p2.first}, p22 = {l2, p2.second};
        return line_intersect(p11, p21) || line_intersect(p11, p22) || line_intersect(p12, p21) || line_intersect(p12, p22);
    };
    auto mark_path = [&](int u, int v, int mark) {
        for(; !is_anc(u, v); u = par[u]) mem_cyc[u] |= mark;
        for(; u != v; v = par[v]) mem_cyc[v] |= mark;
        mem_cyc[u] |= mark;
    };
    mark_path(extra_edge[0].first, extra_edge[0].second, 1);
    mark_path(extra_edge[1].first, extra_edge[1].second, 2);
    for(int i = 0; i < n; i++) {
        int deg = 0;
        for(int j: g[i]) deg += mem_cyc[j] > 0;
        if(deg > 2) mem_cyc[i] = 4;
    }
    for(int i = 0; i < n; i++) {
        if(mem_cyc[i] > 0) dfs2(dfs2, i, i);
    }
    bool t1 = !path_intersect(extra_edge[0], extra_edge[1]);
    for(int i = 0, u, v; i < q; i++) {
        cin >> u >> v; --u, --v;
        int c1 = path_intersect({u, v}, extra_edge[0]), c2 = path_intersect({u, v}, extra_edge[1]);
        if(t1) {
            cout << (1 + c1) * (1 + c2) << '\n';
        } else {
            if(!c1 && !c2) {
                cout << "1\n";
            } else if(mem_cyc[u] != 4 && mem_cyc[v] != 4 && mem_cyc[u] != mem_cyc[v]) {
                cout << "4\n";
            } else {
                cout << "3\n";
            }
        }
    }
}