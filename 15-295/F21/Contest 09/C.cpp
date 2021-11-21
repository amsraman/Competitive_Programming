#include <bits/stdc++.h>

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

int n, sz[6];
map<string, int> ind;
string sizes[6] = {"S", "M", "L", "XL", "XXL", "XXXL"};\

int main() {
    for(int i = 0; i < 6; i++) {
        cin >> sz[i];
        ind[sizes[i]] = i;
    }
    cin >> n;
    FlowNetwork<int> flow(n + 8);
    for(int i = 0; i < 6; i++) {
        flow.add_edge(0, i + 1, sz[i]);
    }
    for(int i = 0; i < n; i++) {
        string sizes;
        cin >> sizes;
        int com_pos = -1;
        for(int i = 0; i < sizes.length(); i++) {
            if(sizes[i] == ',') {
                com_pos = i;
            }
        }
        if(com_pos == -1) {
            flow.add_edge(ind[sizes] + 1, i + 7, 1);
        } else {
            string s1 = sizes.substr(0, com_pos);
            string s2 = sizes.substr(com_pos + 1, sizes.length() - com_pos - 1);
            flow.add_edge(ind[s1] + 1, i + 7, 1);
            flow.add_edge(ind[s2] + 1, i + 7, 1);
        }
        flow.add_edge(i + 7, n + 7, 1);
    }
    if(flow.dinic_flow(0, n + 7) == n) {
        cout << "YES" << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 6; j++) {
                if(flow.edge_capacity[i + 7][j + 1] == 1) {
                    cout << sizes[j] << endl;
                }
            }
        }
    } else {
        cout << "NO" << endl;
    }
}