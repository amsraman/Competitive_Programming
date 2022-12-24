// 466 ms
#include <bits/stdc++.h>

using namespace std;

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
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        g[a].push_back(b);
    }
    TarjanSCC scc(g);
    int ct = scc.scc_count;
    cout << ct << '\n';
    for(int i = ct - 1; i >= 0; i--) {
        cout << scc.comps[i].size() << " ";
        for(int u: scc.comps[i]) {
            cout << u << " ";
        }
        cout << '\n';
    }
}