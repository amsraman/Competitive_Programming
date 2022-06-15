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

int n, m, cycle_count;
vector<int> edge_stack;
vector<bool> vis, marked;
vector<array<int, 3>> edges;
vector<vector<int>> cycles;
vector<vector<pair<int, int>>> g;

void dfs(int x, int p) {
    vis[x] = true;
    for(pair<int, int> e: g[x]) {
        if(vis[e.f]) {
            if(e.f == p || marked[e.s]) {
                continue;
            }
            marked[e.s] = true;
            cycles[cycle_count].push_back(e.s);
            for(int i = edge_stack.size() - 1; i >= 0; i--) {
                marked[edge_stack[i]] = true;
                cycles[cycle_count].push_back(edge_stack[i]);
                if(edges[edge_stack[i]][0] == e.f || edges[edge_stack[i]][1] == e.f) {
                    break;
                }
            }
            cycle_count++;
        } else {
            edge_stack.push_back(e.s);
            dfs(e.f, x);
            if(!marked[edge_stack.back()]) {
                cycles[cycle_count++].push_back(edge_stack.back());
            }
            edge_stack.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    g.resize(n);
    for(int i = 0, u, v, c; i < m; i++) {
        cin >> u >> v >> c;
        g[u - 1].push_back({v - 1, i});
        g[v - 1].push_back({u - 1, i});
        edges.push_back({u - 1, v - 1, c - 1});
    }
    cycles.resize(m), marked.resize(m, false), vis.resize(n, false);
    dfs(0, 0);
    FlowNetwork<int> fl(cycle_count + m + 2);
    for(int i = 0; i < cycle_count; i++) {
        fl.add_edge(0, i + 1, max(1, (int) cycles[i].size() - 1));
        for(int j: cycles[i]) {
            fl.add_edge(i + 1, cycle_count + edges[j][2] + 1, 1);
        }
    }
    for(int i = 0; i < m; i++) {
        fl.add_edge(cycle_count + i + 1, cycle_count + m + 1, 1);
    }
    cout << fl.dinic_flow(0, cycle_count + m + 1) << '\n';
}