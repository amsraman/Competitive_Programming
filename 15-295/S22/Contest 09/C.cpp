#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 0x3f3f3f3f;

int n, m, str[100];
ll ans;
vector<int> atk, def;

template <typename T_f, typename T_c>
struct CostFlowNetwork {
    size_t nn, mm = 0;
    T_f f_inf = 0x3f3f3f3f;
    T_c c_inf = 0xfffffffffffffff;
    vector<pair<size_t, size_t>> path;
    vector<T_c> dist;
    vector<vector<pair<size_t, size_t>>> graph;
    vector<T_f> init_capacity, edge_capacity;
    vector<T_c> costs;

    CostFlowNetwork(size_t n): nn(n), path(n), dist(n), graph(n) {};

    void add_edge(size_t ind1, size_t ind2, T_f capacity, T_c cost) {
        size_t front_edge = mm++, back_edge = mm++;
        graph[ind1].push_back({ind2, front_edge});
        graph[ind2].push_back({ind1, back_edge});
        init_capacity.push_back(capacity), init_capacity.push_back(0);
        edge_capacity.push_back(0), edge_capacity.push_back(0);
        costs.push_back(cost), costs.push_back(-cost);
    }

    bool spfa(size_t source, size_t sink) {
        fill(dist.begin(), dist.end(), c_inf);
        dist[source] = 0;
        vector<bool> in_queue(nn, false);
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
        for(size_t i = 0; i < mm; i++) {
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
            ans = max(ans, INF * max(0, flow - n) - cost);
        }
        return {flow, cost};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0, st; i < n; i++) {
        string pos;
        cin >> pos >> st;
        if(pos == "ATK") {
            atk.push_back(st);
        } else {
            def.push_back(st);
        }
    }
    for(int i = 0; i < m; i++) {
        cin >> str[i];
    }
    CostFlowNetwork<int, ll> net(n + m + 2);
    for(int i = 0; i < m; i++) {
        net.add_edge(0, i + 1, 1, 0);
        net.add_edge(i + 1, n + m + 1, 1, INF - str[i]);
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < atk.size(); j++) {
            int ind = j + m + 1;
            if(str[i] >= atk[j]) {
                net.add_edge(i + 1, ind, 1, atk[j] - str[i]);
            }
        }
        for(int j = 0; j < def.size(); j++) {
            int ind = j + atk.size() + m + 1;
            if(str[i] > def[j]) {
                net.add_edge(i + 1, ind, 1, 0);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        net.add_edge(i + m + 1, n + m + 1, 1, 0);
    }
    net.min_cost_max_flow(0, n + m + 1);
    cout << ans << '\n';
}