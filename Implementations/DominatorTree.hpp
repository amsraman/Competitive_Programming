vector<int> dominator_tree(const vector<vector<int>> & graph, int source) {
    int n = graph.size();
    vector<int> ord, in(n, -1), par(n), mn(n), link(n), sdom(n), dom(n, -1);
    iota(mn.begin(), mn.end(), 0), iota(link.begin(), link.end(), 0), iota(sdom.begin(), sdom.end(), 0);
    vector<vector<int>> reverse_graph(n), bucket(n);
    auto dfs = [&](auto rec, int u) -> void {
        in[u] = ord.size(); ord.push_back(u);
        for(int v: graph[u]) {
            if(in[v] == -1) {
                par[v] = u;
                rec(rec, v);
            }
            reverse_graph[v].push_back(u);
        }
    };
    auto dfs_cmp = [&](int u, int v) {
        return in[u] < in[v];
    };
    auto find = [&](auto rec, int u) -> int {
        if(link[u] != u) {
            int v = rec(rec, link[u]);
            link[u] = link[link[u]];
            if(dfs_cmp(sdom[v], sdom[mn[u]])) mn[u] = v;
        }
        return mn[u];
    };
    dfs(dfs, source);
    reverse(ord.begin(), ord.end());
    for(int u: ord) {
        for(int v: reverse_graph[u]) {
            if(in[v] != -1) {
                int w = find(find, v);
                if(dfs_cmp(sdom[w], sdom[u])) sdom[u] = sdom[w]; 
            }
        }
        bucket[sdom[u]].push_back(u);
        for(int v: bucket[u]) {
            int w = find(find, v);
            dom[v] = sdom[v] == sdom[w] ? sdom[v] : w;
        }
        for(int v: graph[u]) {
            if(par[v] == u) link[v] = u;
        }
    }
    ord.pop_back(); reverse(ord.begin(), ord.end());
    for(int u: ord) {
        if(dom[u] != sdom[u]) dom[u] = dom[dom[u]];
    }
    return dom;
}