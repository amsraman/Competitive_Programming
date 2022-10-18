template <typename T_f, typename T_c>
struct CostFlowNetwork {
    size_t n, m = 0;
    T_f f_inf = numeric_limits<T_f>::max();
    T_c c_inf = numeric_limits<T_c>::max();
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
            size_t u = q.front(); q.pop();
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
