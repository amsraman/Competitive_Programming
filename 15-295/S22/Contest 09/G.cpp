#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

template <typename T>
struct FlowNetwork {
    size_t n;
    T INF = 0x3f3f3f3f;
    vector<size_t> level, ptr;
    vector<vector<size_t>> graph;
    vector<map<size_t, T>> init_capacity, edge_capacity;

    FlowNetwork(size_t n): n(n), level(n), ptr(n), graph(n), init_capacity(n), edge_capacity(n) {
        for(size_t i = 0; i < n; i++) {
            // init_capacity[i].resize(n, 0);
            // edge_capacity[i].resize(n, 0);
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
            for(auto j: init_capacity[i]) {
                edge_capacity[i][j.first] = j.second;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vector<vector<int>> div(5e4 + 1);
    for(int i = 1; i <= 5e4; i++) {
        for(int j = 2 * i; j <= 5e4; j += i) {
            div[j].push_back(i);
        }
    }
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n), id(5e4 + 1, -1);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            id[a[i]] = i;
        }
        FlowNetwork<int> match(4 * n + 2);
        vector<pair<int, int>> edges;
        for(int i = 0; i < n; i++) {
            for(int j: div[a[i]]) {
                if(id[j] != -1) {
                    edges.push_back({id[j], i});
                    edges.push_back({id[j] + n, i + n});
                }
            }
            edges.push_back({i, i + n});
        }
        for(int i = 0; i < 2 * n; i++) {
            match.add_edge(0, i + 1, 1);
            match.add_edge(2 * n + i + 1, 4 * n + 1, 1);
        }
        for(pair<int, int> e: edges) {
            match.add_edge(e.f + 1, e.s + 2 * n + 1, 1);
        }
        cout << match.dinic_flow(0, 4 * n + 1) - n << '\n';
    }
}
