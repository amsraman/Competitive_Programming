struct TarjanSCC {
    int n, time = 0, scc_count = 0;
    vector<int> lp, scc; // sccs are enumerated in reverse topological order
    stack<int> dfs_stack;
    vector<vector<int>> graph, comps;
    int dfs(int u) {
        int low = lp[u] = ++time, v;
        dfs_stack.push(u);
        for(int v: graph[u]) {
            if(scc[v] < 0) {
                low = min(low, lp[v] ?: dfs(v));
            }
        }
        if(low == lp[u]) {
            comps.emplace_back(); scc_count++;
            do {
                v = dfs_stack.top(); dfs_stack.pop();
                scc[v] = scc_count - 1, comps[scc_count - 1].push_back(v);
            } while(v != u);
        }
        return lp[u] = low;
    }
    TarjanSCC(const vector<vector<int>> & graph): n((int) graph.size()), lp(n), scc(n, -1), graph(graph) {
        for(int i = 0; i < n; i++) {
            if(scc[i] < 0) {
                dfs(i);
            }
        }
    }
    vector<vector<int>> condensation_graph() { // completely untested but I think it should just work
        vector<vector<int>> res(scc_count);
        vector<bool> vis(scc_count, false);
        for(int comp = 0; comp < scc_count; comp++) {
            for(int u: comps[comp]) {
                for(int v: graph[u]) {
                    if(!vis[scc[v]]) {
                        res[comp].push_back(scc[v]);
                        vis[scc[v]] = true;
                    }
                }
            }
            for(int v: res[comp]) {
                vis[v] = false;
            }
        }
        return res;
    }
};