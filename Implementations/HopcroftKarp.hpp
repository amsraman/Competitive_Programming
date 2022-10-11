struct HopcroftKarp {
    int n;
    vector<int> dist, pair_u, pair_v;
    vector<vector<int>> graph;

    HopcroftKarp(int n): n(n), dist(n), pair_u(n), pair_v(n), graph(n) {};

    void add_edge(int u, int v) {
        // u \in U, v \in V
        graph[u].push_back(v);
    }

    bool bfs() {
        bool found = false;
        queue<int> q;
        for(int i = 0; i < n; i++) {
            if(pair_u[i] == -1) {
                dist[i] = 0, q.push(i);
            } else {
                dist[i] = n + 1;
            }
        }
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v: graph[u]) {
                if(pair_v[v] != -1 && dist[pair_v[v]] == n + 1) {
                    dist[pair_v[v]] = dist[u] + 1, q.push(pair_v[v]);
                } else if(pair_v[v] == -1) {
                    found = true;
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for(int v: graph[u]) {
            if(pair_v[v] == -1) {
                pair_u[u] = v, pair_v[v] = u;
                return true;
            }
        }
        for(int v: graph[u]) {
            if(dist[pair_v[v]] == dist[u] + 1 && dfs(pair_v[v])) {
                pair_u[u] = v, pair_v[v] = u;
                return true;
            }
        }
        return false;
    }

    int max_matching() {
        int res = 0;
        fill(pair_u.begin(), pair_u.end(), -1);
        fill(pair_v.begin(), pair_v.end(), -1);
        while(bfs()) {
            for(int i = 0; i < n; i++) {
                if(pair_u[i] == -1) {
                    res += dfs(i);
                }
            }
        }
        return res;
    }
};