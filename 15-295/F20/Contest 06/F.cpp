#include <bits/stdc++.h>

using namespace std;

template <typename T_f, typename T_c>
struct CostFlowNetwork {
    size_t n;
    T_c INF = 0x3f3f3f3f;
    vector<size_t> path;
    vector<T_c> dist;
    vector<vector<size_t>> graph;
    vector<vector<T_f>> init_capacity, edge_capacity;
    vector<vector<T_c>> costs;

    CostFlowNetwork(size_t n): n(n), path(n), dist(n), graph(n), init_capacity(n), edge_capacity(n), costs(n) {
        for(size_t i = 0; i < n; i++) {
            init_capacity[i].resize(n, 0);
            edge_capacity[i].resize(n, 0);
            costs[i].resize(n, 0);
        }
    };

    void add_edge(size_t ind1, size_t ind2, T_f capacity, T_c cost) {
        if(init_capacity[ind1][ind2] == 0) {
            graph[ind1].push_back(ind2);
            graph[ind2].push_back(ind1);
        }
        init_capacity[ind1][ind2] += capacity;
        costs[ind1][ind2] += cost;
        costs[ind2][ind1] -= cost;
    }
    
    bool spfa(size_t source, size_t sink) {
        fill(dist.begin(), dist.end(), INF);
        dist[source] = 0;
        vector<bool> in_queue(n, false);
        queue<size_t> q;
        q.push(source);
        in_queue[source] = true;
        while(!q.empty()) {
            size_t u = q.front();
            q.pop();
            in_queue[u] = false;
            for(size_t v: graph[u]) {
                if(edge_capacity[u][v] > 0 && dist[u] + costs[u][v] < dist[v]) {
                    dist[v] = dist[u] + costs[u][v];
                    path[v] = u;
                    if(!in_queue[v]) {
                        in_queue[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        return dist[sink] < INF;
    }

    pair<T_f, T_c> min_cost_max_flow(size_t source, size_t sink) {
        T_f flow = 0;
        T_c cost = 0;
        for(size_t i = 0; i < n; i++) {
            for(size_t j = 0; j < n; j++) {
                edge_capacity[i][j] = init_capacity[i][j];
            }
        }
        while(spfa(source, sink)) {
            T_f aug_path = INF;
            size_t cur_vertex = sink;
            while(cur_vertex != source) {
                aug_path = min(aug_path, edge_capacity[path[cur_vertex]][cur_vertex]);
                cur_vertex = path[cur_vertex];
            }
            cur_vertex = sink;
            while(cur_vertex != source) {
                edge_capacity[path[cur_vertex]][cur_vertex] -= aug_path;
                edge_capacity[cur_vertex][path[cur_vertex]] += aug_path;
                cur_vertex = path[cur_vertex];
            }
            flow += aug_path, cost += dist[sink];
        }
        return {flow, cost};
    }
};

int t, n, dist;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        CostFlowNetwork<int, int> paths(2 * n + 2);
        for(int i = 0; i < n; i++) {
            paths.add_edge(0, i + 1, 1, 0);
            paths.add_edge(i + n + 1, 2 * n + 1, 1, 0);
            for(int j = i + 1; j < n; j++) {
                cin >> dist;
                paths.add_edge(i + 1, j + n + 1, 1, dist);
                paths.add_edge(j + 1, i + n + 1, 1, dist);
            }
        }
        cout << "Case " << _ << ": " << paths.min_cost_max_flow(0, 2 * n + 1).second << '\n';
    }
}