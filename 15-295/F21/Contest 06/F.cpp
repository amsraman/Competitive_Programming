#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define f first
#define s second

using namespace std;

template <typename T_f, typename T_c>
struct CostFlowNetwork {
    size_t n, m = 0;
    T_c INF = 0x3f3f3f3f;
    vector<pair<size_t, size_t>> path;
    vector<T_c> dist;
    vector<vector<pair<size_t, size_t>>> graph;
    vector<T_f> init_capacity, edge_capacity;
    vector<T_c> costs;

    vector<pair<T_c, T_c>> critical_points;

    CostFlowNetwork(size_t n): n(n), path(n), dist(n), graph(n) {};

    void add_edge(size_t ind1, size_t ind2, T_f capacity, T_c cost) {
        size_t front_edge = m++, back_edge = m++;
        graph[ind1].push_back({ind2, front_edge});
        graph[ind2].push_back({ind1, back_edge});
        init_capacity.push_back(capacity), init_capacity.push_back(0);
        edge_capacity.push_back(0), edge_capacity.push_back(0);
        costs.push_back(cost), costs.push_back(-cost);
    }
    
    bool bellman_ford(size_t source, size_t sink) {
        fill(dist.begin(), dist.end(), INF);
        dist[source] = 0; 
        for(size_t iter = 0; iter < n - 1; iter++) {
            for(size_t i = 0; i < n; i++) {
                for(pair<size_t, size_t> e: graph[i]) {
                    if(edge_capacity[e.second] > 0 && dist[i] + costs[e.second] < dist[e.first]) {
                        dist[e.first] = dist[i] + costs[e.second];
                        path[e.first] = {i, e.second};
                    }
                }
            }
        }
        return dist[sink] < INF;
    }

    pair<T_f, T_c> min_cost_max_flow(size_t source, size_t sink) {
        T_f flow = 0;
        T_c cost = 0;
        for(size_t i = 0; i < m; i++) {
            edge_capacity[i] = init_capacity[i];
        }
        while(bellman_ford(source, sink)) {
            T_f aug_path = INF;
            size_t cur_vertex = sink;
            while(cur_vertex != source) {
                aug_path = min(aug_path, edge_capacity[path[cur_vertex].second]);
                cur_vertex = path[cur_vertex].first;
            }
            cur_vertex = sink;
            while(cur_vertex != source) {
                edge_capacity[path[cur_vertex].second] -= aug_path;
                edge_capacity[path[cur_vertex].second ^ 1] += aug_path;
                cur_vertex = path[cur_vertex].first;
            }
            // x: the extra weight you'd have to have added for this to be the shortest path
            // y: the shortest path
            critical_points.push_back({dist[sink] * flow - cost, dist[sink]});
            flow += aug_path, cost += aug_path * dist[sink];
        }
        critical_points.push_back({INF * flow - cost, INF});
        return {flow, cost};
    }
};

int n, m, q;

int main() {
    cin >> n >> m;
    CostFlowNetwork<ll, ll> dual(n);
    for(int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        dual.add_edge(u - 1, v - 1, 1, w);
    }
    pair<ll, ll> mcmf = dual.min_cost_max_flow(0, n - 1);
    cin >> q;
    for(int i = 0, x; i < q; i++) {
        cin >> x;
        ld ans = 0;
        auto it = lower_bound(dual.critical_points.begin(), dual.critical_points.end(), pair<ll, ll> {x + 1, 0});
        ans = (it - 1)->s + (ld) (x - (it - 1)->f) * (it->s - (it - 1)->s) / (it->f - (it - 1)->f);
        cout << fixed << setprecision(9) << ans << endl;
    }
}