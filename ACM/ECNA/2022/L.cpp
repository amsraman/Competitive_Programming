#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <typename T_f, typename T_c>
struct CostFlowNetwork {
    int n, m = 0;
    T_f f_inf = numeric_limits<T_f>::max();
    T_c c_inf = numeric_limits<T_c>::max();
    vector<pair<int, int>> path;
    vector<T_c> dist;
    vector<vector<pair<int, int>>> graph;
    vector<T_f> init_capacity, edge_capacity;
    vector<T_c> costs;
    CostFlowNetwork(int n): n(n), path(n), dist(n), graph(n) {};
    void add_edge(int ind1, int ind2, T_f capacity, T_c cost) {
        int front_edge = m++, back_edge = m++;
        graph[ind1].emplace_back(ind2, front_edge);
        graph[ind2].emplace_back(ind1, back_edge);
        init_capacity.push_back(capacity), init_capacity.push_back(0);
        edge_capacity.push_back(0), edge_capacity.push_back(0);
        costs.push_back(cost), costs.push_back(-cost);
    }
    bool spfa(int source, int sink) {
        fill(dist.begin(), dist.end(), c_inf); dist[source] = 0;
        vector<bool> in_queue(n, false);
        queue<int> q; q.push(source); in_queue[source] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            in_queue[u] = false;
            for(pair<int, int> e: graph[u]) {
                if(edge_capacity[e.second] > 0 && dist[u] < c_inf && dist[u] + costs[e.second] < dist[e.first]) {
                    dist[e.first] = dist[u] + costs[e.second];
                    path[e.first] = {u, e.second};
                    if(!in_queue[e.first]) {
                        in_queue[e.first] = true;
                        q.push(e.first);
                    }
                }
            }
        }
        return dist[sink] < c_inf;
    }
    pair<T_f, T_c> min_cost_max_flow(int source, int sink) {
        T_f flow = 0; T_c cost = 0;
        for(int i = 0; i < m; i++) {
            edge_capacity[i] = init_capacity[i];
        }
        while(spfa(source, sink)) {
            T_f aug_path = f_inf;
            int cur_vertex = sink;
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
            flow += aug_path, cost += dist[sink] * aug_path;
        }
        return {flow, cost};
    }
};

const int INF = 1e9;

int main() {
    int n, m; cin >> n >> m;
    CostFlowNetwork<ll, ll> cfn(n + m + 2);
    vector<vector<int>> num(n, vector<int>(m));
    vector<int> tot(m, 0);
    vector<vector<int>> dist(n, vector<int>(n, INF));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> num[i][j];
            tot[j] += num[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        cfn.add_edge(0, i + 1, 1, 0);
    }
    for(int i = 0; i < m; i++) {
        cfn.add_edge(i + n + 1, n + m + 1, 1, 0);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int hi; cin >> hi;
            if(hi != -1) dist[i][j] = hi;
        }
    }
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            // matching i to j
            ll tot = 0;
            for(int k = 0; k < n; k++) {
                tot += dist[k][i] * num[k][j];
            }
            cfn.add_edge(i + 1, j + n + 1, 1, tot);
        }
    }
    auto [flow, cost] = cfn.min_cost_max_flow(0, n + m + 1);
    cout << cost << '\n';
}