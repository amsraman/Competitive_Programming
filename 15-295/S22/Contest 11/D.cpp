#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <typename T_f, typename T_c>
struct CostFlowNetwork {
    size_t n, m = 0;
    T_f f_inf = 0x3f3f3f3f;
    T_c c_inf = 0xfffffffffffffff;
    vector<pair<size_t, size_t>> path;
    vector<T_c> dist;
    vector<vector<pair<size_t, size_t>>> graph;
    vector<T_f> init_capacity, edge_capacity;
    vector<T_c> costs;

    CostFlowNetwork(size_t n): n(n), path(n), dist(n), graph(n) {};

    void add_edge(size_t ind1, size_t ind2, T_f capacity, T_c cost) {
        size_t front_edge = m++, back_edge = m++;
        graph[ind1].push_back({ind2, front_edge});
        graph[ind2].push_back({ind1, back_edge});
        init_capacity.push_back(capacity), init_capacity.push_back(0);
        edge_capacity.push_back(0), edge_capacity.push_back(0);
        costs.push_back(cost), costs.push_back(-cost);
    }

    bool spfa(size_t source, size_t sink) {
        fill(dist.begin(), dist.end(), c_inf);
        dist[source] = 0;
        vector<bool> in_queue(n, false);
        queue<size_t> q;
        q.push(source);
        in_queue[source] = true;
        while(!q.empty()) {
            size_t u = q.front();
            q.pop();
            in_queue[u] = false;
            for(pair<size_t, size_t> e: graph[u]) {
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

    pair<T_f, T_c> min_cost_max_flow(size_t source, size_t sink) {
        T_f flow = 0;
        T_c cost = 0;
        for(size_t i = 0; i < m; i++) {
            edge_capacity[i] = init_capacity[i];
        }
        while(spfa(source, sink)) {
            T_f aug_path = f_inf;
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
            flow += aug_path, cost += dist[sink] * aug_path;
        }
        return {flow, cost};
    }
};


int n, l[500][500];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> l[i][j];
        }
    }
    int odds = (n + 1) / 2;
    CostFlowNetwork<int, ll> net(2 * odds + 2);
    for(int i = 0; i < odds; i++) {
        net.add_edge(0, i + 1, 1, 0);
        net.add_edge(i + odds + 1, 2 * odds + 1, 1, 0);
    }
    for(int i = 0; i < n; i += 2) {
        for(int j = 0; j < n; j += 2) {
            int lc = (j == 0 ? 0 : l[j - 1][i]), rc = (j == n - 1 ? 0 : l[i][j + 1]);
            net.add_edge(i / 2 + 1, j / 2 + odds + 1, 1, lc + rc);
        }
    }
    cout << net.min_cost_max_flow(0, 2 * odds + 1).second << endl;
}