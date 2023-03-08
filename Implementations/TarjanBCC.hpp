struct TarjanBCC {
    int n, time = 0, bcc_count = 0;
    vector<int> in, lp, bcc;
    vector<bool> cut;
    stack<pair<int, int>> dfs_stack;
    vector<vector<int>> graph, comp_vertices;
    vector<vector<pair<int, int>>> comp_edges;
    int dfs(int u, int p = -1) {
        in[u] = lp[u] = ++time;
        int ch = 0; pair<int, int> lst_edge;
        for(int v: graph[u]) {
            if(in[v] == -1) {
                ++ch; dfs_stack.emplace(u, v);
                lp[u] = min(lp[u], dfs(v, u));
                if(lp[v] >= in[u]) {
                    if(p != -1 && !cut[u]) cut[u] = true, bcc[u] = bcc_count++;
                    bcc_count++;
                    do {
                        comp_edges[bcc_count - 1].emplace_back(lst_edge = dfs_stack.top()); dfs_stack.pop();
                    } while(lst_edge != make_pair(u, v));
                }
            } else if(v != p && in[v] < in[u]) {
                lp[u] = min(lp[u], in[v]), dfs_stack.emplace(u, v);
            }
        }
        if(p == -1 && ch > 1) cut[u] = true, bcc[u] = bcc_count++;
        return lp[u];
    }
    TarjanBCC(const vector<vector<int>> & graph): n((int) graph.size()), in(n, -1), lp(n), bcc(n, -1), cut(n, false), graph(graph), comp_edges(2 * n) {
        for(int i = 0; i < n; i++) {
            if(in[i] == -1) {
                dfs(i);
            }
        }
        comp_edges.resize(bcc_count); comp_vertices.resize(bcc_count);
        vector<bool> vis(n, false);
        for(int i = 0; i < bcc_count; i++) {
            for(auto [u, v]: comp_edges[i]) {
                if(!vis[u]) {
                    if(!cut[u]) bcc[u] = i;
                    comp_vertices[i].push_back(u), vis[u] = true;
                }
                if(!vis[v]) {
                    if(!cut[v]) bcc[v] = i;
                    comp_vertices[i].push_back(v), vis[v] = true;
                }
            }
            for(auto [u, v]: comp_edges[i]) vis[u] = vis[v] = false;
        }
    }
    vector<vector<int>> block_cut_forest() {
        vector<vector<int>> res(bcc_count);
        for(int i = 0; i < bcc_count; i++) {
            for(int u: comp_vertices[i]) {
                if(cut[u]) {
                    res[bcc[u]].push_back(i);
                    res[i].push_back(bcc[u]);
                }
            }
        }
        return res;
    }
};