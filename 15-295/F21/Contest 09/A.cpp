#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct FlowNetwork {
    size_t n;
    T INF = 0x3f3f3f3f;
    vector<size_t> level, ptr;
    vector<vector<size_t>> graph;
    vector<vector<T>> init_capacity, edge_capacity;

    FlowNetwork(size_t n): n(n), level(n), ptr(n), graph(n), init_capacity(n), edge_capacity(n) {
        for(size_t i = 0; i < n; i++) {
            init_capacity[i].resize(n, 0);
            edge_capacity[i].resize(n, 0);
        }
    };

    void add_edge(size_t ind1, size_t ind2, T weight) {
        if(init_capacity[ind1][ind2] == 0) {
            graph[ind1].push_back(ind2);
            graph[ind2].push_back(ind1);
        }
        init_capacity[ind1][ind2] += weight;
    }

    T dfs(size_t start, T cur_bottleneck, size_t end) {
        if(start == end) {
            return cur_bottleneck;
        }
        while(ptr[start] < graph[start].size()) {
            size_t neighbor = graph[start][ptr[start]];
            while(level[neighbor] != level[start] + 1 || edge_capacity[start][neighbor] == 0) {
                ++ptr[start];
                if(ptr[start] == graph[start].size()) {
                    break;
                }
                neighbor = graph[start][ptr[start]];
            }
            if(ptr[start] == graph[start].size()) {
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

    T dinic_flow(size_t source, size_t sink) {
        T flow = 0;
        bool path_exists = true;
        for(size_t i = 0; i < n; i++) {
            for(size_t j = 0; j < n; j++) {
                edge_capacity[i][j] = init_capacity[i][j];
            }
        }
        while(path_exists) {
            queue<size_t> q;
            fill(level.begin(), level.end(), 0);
            fill(ptr.begin(), ptr.end(), 0);
            q.push(source), level[source] = 1;
            while(!q.empty()) {
                size_t cur_node = q.front();
                q.pop();
                for(size_t next_node: graph[cur_node]) {
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

int n, m, a[100], b[100], sum_a, sum_b;

int main() {
    cin >> n >> m;
    FlowNetwork<int> cities(2 * n + 2);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        cities.add_edge(0, i + 1, a[i]);
        cities.add_edge(i + 1, i + n + 1, a[i]);
        sum_a += a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        cities.add_edge(i + n + 1, 2 * n + 1, b[i]);
        sum_b += b[i];
    }
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        cities.add_edge(u, v + n, a[u - 1]);
        cities.add_edge(v, u + n, a[v - 1]);
    }
    if(sum_a != sum_b) {
        cout << "NO" << endl;
    } else if(cities.dinic_flow(0, 2 * n + 1) != sum_a) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << cities.edge_capacity[j + n + 1][i + 1] << " ";
            }
            cout << endl;
        }
    }
}