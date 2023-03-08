template <typename T>
vector<pair<T, int>> dijkstra(vector<vector<pair<int, T>>> & graph, int s) {
    // Returns (distance, parent) pairs
    int n = graph.size();
    T INF = numeric_limits<T>::max();
    vector<pair<T, int>> dist(n, {INF, -1});
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
    q.push({0, s}), dist[s] = {0, -1};
    while(!q.empty()) {
        pair<T, int> tp = q.top(); q.pop();
        if(tp.first > dist[tp.second].first) {
            continue;
        }
        int u = tp.second;
        for(pair<int, T> e: graph[u]) {
            if(dist[u].first + e.second < dist[e.first].first) {
                dist[e.first] = {dist[u].first + e.second, u};
                q.push({dist[e.first].first, e.first});
            }
        }
    }
    return dist;
}