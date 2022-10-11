struct TwoSat {
    int var_count, time;
    vector<int> scc, lp, assignment;
    stack<int> dfs_stack;
    vector<vector<int>> implication_graph;
    
    TwoSat(int n = 0): var_count(n), implication_graph(2 * n) {}

    int add_var() {
        implication_graph.emplace_back();
        implication_graph.emplace_back();
        return var_count++;
    }

    void add_clause(int u, int v) {
        implication_graph[u ^ 1].push_back(v);
        implication_graph[v ^ 1].push_back(u);
    }

    void either(int u, int v) {
        add_clause(u, v);
        add_clause(u ^ 1, v ^ 1);
    }

    void same(int u, int v) {
        either(u, v ^ 1);
    }

    void set(int u) {
        either(u, u);
    }

    void at_most_one(vector<int> & vars) {
        vector<int> pre, suf;
        for(int i = 0; i < vars.size(); i++) {
            pre.push_back(add_var()), suf.push_back(add_var());
            add_clause(pre[i] << 1 ^ 1, vars[i] ^ 1);
            add_clause(suf[i] << 1 ^ 1, vars[i] ^ 1);
            if(i > 0) {
                add_clause(pre[i] << 1 ^ 1, pre[i - 1] << 1);
                add_clause(suf[i - 1] << 1 ^ 1, suf[i] << 1);
                add_clause(vars[i] ^ 1, pre[i - 1] << 1);
                add_clause(vars[i - 1] ^ 1, suf[i] << 1);
            }
        }
    }

    int dfs(int u) {
        int low = lp[u] = ++time, v;
        dfs_stack.push(u);
        for(int v: implication_graph[u]) {
            if(!scc[v]) {
                low = min(low, lp[v] ?: dfs(v));
            }
        }
        ++time;
        if(low == lp[u]) {
            do {
                v = dfs_stack.top();
                dfs_stack.pop();
                scc[v] = time;
                if(assignment[v >> 1] == -1) {
                    assignment[v >> 1] = v & 1;
                }
            } while(v != u);
        }
        return lp[u] = low;
    }

    bool solvable() {
        scc.assign(var_count << 1, 0), lp.assign(var_count << 1, 0);
        assignment.assign(var_count, -1);
        time = 0;
        for(int i = 0; i < var_count << 1; i++) {
            if(!scc[i]) {
                dfs(i);
            }
        }
        for(int i = 0; i < var_count; i++) {
            if(scc[i << 1] == scc[i << 1 ^ 1]) {
                return false;
            }
        }
        return true;
    }
};