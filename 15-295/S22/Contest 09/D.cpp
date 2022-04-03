#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

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

int n, m, s, b, k, h, sloc[1000], a[1000], f[1000], bloc[1000], d[1000], dist[100][100];

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) {
                dist[i][j] = INF;
            }
        }
    }
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        dist[u - 1][v - 1] = 1;
    }
    cin >> s >> b >> k >> h;
    for(int i = 0; i < s; i++) {
        cin >> sloc[i] >> a[i] >> f[i];
        --sloc[i];
    }
    for(int i = 0; i < b; i++) {
        cin >> bloc[i] >> d[i];
        --bloc[i];
    }
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    FlowNetwork<int> net(s + b + 2);
    for(int i = 0; i < s; i++) {
        net.add_edge(0, i + 1, 1);
    }
    for(int i = 0; i < s; i++) {
        for(int j = 0; j < b; j++) {
            if(a[i] >= d[j] && f[i] >= dist[sloc[i]][bloc[i]]) {
                net.add_edge(i + 1, j + s + 1, 1);
            }
        }
    }
    for(int i = 0; i < b; i++) {
        net.add_edge(i + s + 1, b + s + 1, 1);
    }
    int flow = net.dinic_flow(0, b + s + 1);
    cout << min(1LL * s * h, 1LL * k * flow) << endl;
}