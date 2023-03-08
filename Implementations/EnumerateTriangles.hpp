void enumerate_triangles(const vector<vector<int>> & graph, function<void (int, int, int)> f) {
    int n = graph.size();
    vector<vector<int>> bigger_neighbors(n);
    for(int i = 0; i < n; i++) {
        for(int j: graph[i]) {
            if(graph[j].size() > graph[i].size() || (graph[j].size() == graph[i].size() && j > i)) {
                bigger_neighbors[i].push_back(j);
            }
        }
    }
    vector<bool> neighbor(n, false);
    for(int i = 0; i < n; i++) {
        for(int j: bigger_neighbors[i]) neighbor[j] = true;
        for(int j: bigger_neighbors[i]) {
            for(int k: bigger_neighbors[j]) {
                if(neighbor[k]) {
                    f(i, j, k);
                }
            }
        }
        for(int j: bigger_neighbors[i]) neighbor[j] = false;
    }
}

template <typename T>
T count_four_cycles(const vector<vector<int>> & graph) {
    int n = graph.size();
    T ans = 0;
    vector<pair<int, int>> deg_pair(n);
    for(int i = 0; i < n; i++) deg_pair[i] = {graph[i].size(), i};
    vector<vector<int>> bigger_neighbors(n);
    for(int i = 0; i < n; i++) {
        for(int j: graph[i]) {
            if(deg_pair[j] > deg_pair[i]) {
                bigger_neighbors[i].push_back(j);
            }
        }
    }
    vector<T> two_paths(n, 0);
    for(int i = 0; i < n; i++) {
        for(int j: graph[i]) {
            for(int k: bigger_neighbors[j]) {
                if(deg_pair[k] > deg_pair[i]) {
                    ans += two_paths[k]++;
                }
            }
        }
        for(int j: graph[i]) {
            for(int k: bigger_neighbors[j]) {
                two_paths[k] = 0;
            }
        }
    }
    return ans;
}