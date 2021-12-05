#include <bits/stdc++.h>
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

    CostFlowNetwork(size_t n): n(n), path(n), dist(n), graph(n) {};

    void add_edge(size_t ind1, size_t ind2, T_f capacity, T_c cost) {
        size_t front_edge = m++, back_edge = m++;
        graph[ind1].push_back({ind2, front_edge});
        graph[ind2].push_back({ind1, back_edge});
        init_capacity.push_back(capacity), init_capacity.push_back(0);
        edge_capacity.push_back(0), edge_capacity.push_back(0);
        costs.push_back(cost), costs.push_back(-cost);
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
            for(pair<size_t, size_t> e: graph[u]) {
                if(edge_capacity[e.second] > 0 && dist[u] + costs[e.second] < dist[e.first]) {
                    dist[e.first] = dist[u] + costs[e.second];
                    path[e.first] = {u, e.second};
                    q.push({-dist[e.first], e.first});
                }
            }
        }
        return false;
    }

    pair<T_f, T_c> min_cost_max_flow(size_t source, size_t sink) {
        T_f flow = 0;
        T_c cost = 0;
        for(size_t i = 0; i < m; i++) {
            edge_capacity[i] = init_capacity[i];
        }
        while(dijkstra(source, sink)) {
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
            flow += aug_path, cost += dist[sink] * aug_path;
        }
        return {flow, cost};
    }
};

int n, l[100];
string g, s[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin >> g >> n;
    int tot_len = 0;
    for(int i = 0; i < n; i++) {
        cin >> s[i] >> l[i];
        tot_len += s[i].length();
    }
    CostFlowNetwork<int, int> mcmf(n + tot_len + g.length() + 2);
    for(int i = 1; i <= g.length(); i++) {
        mcmf.add_edge(0, i, 1, 0);
    }
    for(int i = 0; i < n; i++) {
        mcmf.add_edge(g.length() + tot_len + i + 1, g.length() + tot_len + n + 1, l[i], 0);
    }
    for(int i = 0, cur = g.length() + 1; i < n; i++) {
        for(int j = 0; j < s[i].length(); j++) {
            mcmf.add_edge(cur++, g.length() + tot_len + i + 1, 1, i + 1);
        }
    }
    for(int i = 0; i < g.length(); i++) {
        for(int j = 0, cur = g.length() + 1; j < n; j++) {
            for(int k = 0; k < s[j].length(); k++, cur++) {
                if(g[i] == s[j][k]) {
                    mcmf.add_edge(i + 1, cur, 1, 0);
                }
            }
        }
    }
    pair<int, int> res = mcmf.min_cost_max_flow(0, n + tot_len + g.length() + 1);
    cout << (res.f == g.length() ? res.s : -1) << '\n';
}