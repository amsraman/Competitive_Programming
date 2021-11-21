#include <bits/stdc++.h>
#define f first
#define s second

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
    
    bool bellman_ford(size_t source, size_t sink) {
        fill(dist.begin(), dist.end(), INF);
        dist[source] = 0;
        for(size_t iter = 0; iter < n - 1; iter++) {
            for(size_t i = 0; i < n; i++) {
                for(size_t j: graph[i]) {
                    if(edge_capacity[i][j] > 0 && dist[i] + costs[i][j] < dist[j]) {
                        dist[j] = dist[i] + costs[i][j];
                        path[j] = i;
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
        while(bellman_ford(source, sink)) {
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

int n, q, lb[50], ub[50];

int main() {
    cin >> n >> q;
    CostFlowNetwork<int, int> mcmf(3 * n + 2);
    for(int i = 0; i < n; i++) {
        ub[i] = n - 1;
    }
    for(int i = 0, t, l, r, v; i < q; i++) {
        cin >> t >> l >> r >> v;
        if(t == 1) {
            for(int j = l - 1; j < r; j++) {
                lb[j] = max(lb[j], v - 1);
            }
        } else {
            for(int j = l - 1; j < r; j++) {
                ub[j] = min(ub[j], v - 1);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        mcmf.add_edge(0, i + 1, 1, 0);
        mcmf.add_edge(i + 2 * n + 1, 3 * n + 1, 0x3f3f3f3f, 2 * i + 1);
        for(int j = lb[i]; j <= ub[i]; j++) {
            mcmf.add_edge(i + 1, j + n + 1, 1, 0);
        }
        for(int j = 0; j < n; j++) {
            mcmf.add_edge(i + n + 1, j + 2 * n + 1, 1, 0);
        }
    }
    pair<int, int> res = mcmf.min_cost_max_flow(0, 3 * n + 1);
    if(res.f != n) {
        cout << -1 << endl;
    } else {
        cout << res.s << endl;
    }
}