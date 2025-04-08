#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct FlowNetwork {
    int n;
    T INF = numeric_limits<T>::max();
    vector<int> level, ptr;
    vector<vector<int>> graph;
    vector<vector<T>> init_capacity, edge_capacity;
    FlowNetwork(int n): n(n), level(n), ptr(n), graph(n), init_capacity(n), edge_capacity(n) {
        for(int i = 0; i < n; i++) {
            init_capacity[i].resize(n, 0);
            edge_capacity[i].resize(n, 0);
        }
    };
    void add_edge(int ind1, int ind2, T weight) {
        if(init_capacity[ind1][ind2] + init_capacity[ind2][ind1] == 0) {
            graph[ind1].push_back(ind2);
            graph[ind2].push_back(ind1);
        }
        init_capacity[ind1][ind2] += weight;
    }
    T dfs(int start, T cur_bottleneck, int end) {
        if(start == end) {
            return cur_bottleneck;
        }
        while(ptr[start] < (int) graph[start].size()) {
            int neighbor = graph[start][ptr[start]];
            while(level[neighbor] != level[start] + 1 || edge_capacity[start][neighbor] == 0) {
                ++ptr[start];
                if(ptr[start] == (int) graph[start].size()) {
                    break;
                }
                neighbor = graph[start][ptr[start]];
            }
            if(ptr[start] == (int) graph[start].size()) {
                break;
            }
            T final_bottleneck = dfs(neighbor, min(cur_bottleneck, edge_capacity[start][neighbor]), end);
            if(final_bottleneck > 0) {
                edge_capacity[start][neighbor] -= final_bottleneck;
                edge_capacity[neighbor][start] += final_bottleneck;
                return final_bottleneck;
            } else {
                ptr[start]++;
            }
        }
        return 0;
    }
    T dinic_flow(int source, int sink) {
        T flow = 0;
        bool path_exists = true;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                edge_capacity[i][j] = init_capacity[i][j];
            }
        }
        while(path_exists) {
            queue<int> q;
            fill(level.begin(), level.end(), 0);
            fill(ptr.begin(), ptr.end(), 0);
            q.push(source), level[source] = 1;
            while(!q.empty()) {
                int cur_node = q.front();
                q.pop();
                for(int next_node: graph[cur_node]) {
                    if(level[next_node] == 0 && edge_capacity[cur_node][next_node] != 0) {
                        level[next_node] = level[cur_node] + 1;
                        q.push(next_node);
                    }
                }
            }
            path_exists = (level[sink] > 0);
            if(!path_exists) {
                continue;
            }
            while(T extra = dfs(source, INF, sink)) {
                flow += extra;
            }
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int s, r, f, t; cin >> s >> r >> f >> t;
    map<string, int> ind; int ct = 0;
    FlowNetwork<int> fn(s + 2 * t + 2);
    for(int i = 0; i < r; i++) {
        string in; cin >> in;
        ind[in] = ct++;
        fn.add_edge(0, ind[in] + 1, 1);
    }
    for(int i = 0; i < f; i++) {
        string in; cin >> in;
        ind[in] = ct++;
        fn.add_edge(ind[in] + 1, s + 2 * t + 1, 1);
    }
    for(int i = 0; i < t; i++) {
        int n; cin >> n;
        for(int j = 0; j < n; j++) {
            string in; cin >> in;
            if(!ind.count(in)) ind[in] = ct++;
            fn.add_edge(2 * i + s + 2, ind[in] + 1, 1);
            fn.add_edge(ind[in] + 1, 2 * i + s + 1, 1);
        }
        fn.add_edge(2 * i + s + 1, 2 * i + s + 2, 1);
    }
    cout << fn.dinic_flow(0, s + 2 * t + 1) << '\n';
}