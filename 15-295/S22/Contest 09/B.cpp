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

int r, c;
pair<int, int> dir[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
string board[10000];

int conv(int x, int y) {
    return c * x + y;
}

int main() {
    cin >> r >> c;
    for(int i = 0; i < r; i++) {
        cin >> board[i];
    }
    FlowNetwork<int> fn(2 * r * c + 2);
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            fn.add_edge(conv(i, j) + 1, conv(i, j) + r * c + 1, 1);
            if(board[i][j] == 'b') {
                fn.add_edge(0, conv(i, j) + 1, 1);
                for(pair<int, int> d: dir) {
                    if(i + d.f >= 0 && i + d.f < r && j + d.s >= 0 && j + d.s < c && board[i + d.f][j + d.s] == 'e') {
                        fn.add_edge(conv(i, j) + r * c + 1, conv(i + d.f, j + d.s) + 1, 1);
                    }
                }
            } else if(board[i][j] == 'r') {
                fn.add_edge(conv(i, j) + r * c + 1, 2 * r * c + 1, 1);
            } else if(board[i][j] == 'e') {
                for(pair<int, int> d: dir) {
                    if(i + d.f >= 0 && i + d.f < r && j + d.s >= 0 && j + d.s < c && board[i + d.f][j + d.s] != 'b') {
                        fn.add_edge(conv(i, j) + r * c + 1, conv(i + d.f, j + d.s) + 1, 1);
                    }
                }
            }
        }
    }
    cout << fn.dinic_flow(0, 2 * r * c + 1) << endl;
}