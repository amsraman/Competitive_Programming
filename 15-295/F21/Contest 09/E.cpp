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
    
    bool dijkstra(size_t source, size_t sink) {
        fill(dist.begin(), dist.end(), INF);
        dist[source] = 0;
        priority_queue<pair<T_c, size_t>> q;
        q.push({0, source});
        while(!q.empty()) {
            pair<T_c, size_t> tp = q.top();
            q.pop();
            if(dist[tp.s] < -tp.f) {
                continue;
            }
            size_t u = tp.s;
            if(u == sink) {
                return true;
            }
            for(size_t v: graph[u]) {
                if(edge_capacity[u][v] > 0 && dist[u] + costs[u][v] < dist[v]) {
                    dist[v] = dist[u] + costs[u][v];
                    path[v] = u;
                    q.push({-dist[v], v});
                }
            }
        }
        return false;
    }

    pair<T_f, T_c> min_cost_max_flow(size_t source, size_t sink) {
        T_f flow = 0;
        T_c cost = 0;
        for(size_t i = 0; i < n; i++) {
            for(size_t j = 0; j < n; j++) {
                edge_capacity[i][j] = init_capacity[i][j];
            }
        }
        while(dijkstra(source, sink)) {
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

int n;
pair<int, int> points[400];

double dist(int x, int y) {
    pair<double, double> p1 = points[x], p2 = points[y];
    return sqrt((p1.f - p2.f) * (p1.f - p2.f) + (p1.s - p2.s) * (p1.s - p2.s));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> points[i].f >> points[i].s;
    }
    CostFlowNetwork<int, double> mcmf(2 * n + 2);
    for(int i = 0; i < n; i++) {
        mcmf.add_edge(0, i + 1, 1, 0);
        mcmf.add_edge(i + n + 1, 2 * n + 1, 2, 0);
        for(int j = 0; j < n; j++) {
            if(i != j && points[j].s > points[i].s) {
                mcmf.add_edge(i + 1, n + j + 1, 1, dist(i, j));
            }
        }
    }
    pair<int, double> res = mcmf.min_cost_max_flow(0, 2 * n + 1);
    if(res.f != n - 1) {
        cout << -1 << '\n';
    } else {
        cout << fixed << setprecision(10) << res.s << '\n';
    }
}