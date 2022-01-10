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

    FlowNetwork(size_t n): n(n), level(n), ptr(n), graph(n), init_capacity(n), edge_capacity(n) {};

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

int n, m, comp[100][100], cc;
pair<int, int> dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
string grid[100];
set<int> border, col[2];
set<pair<int, int>> edges;

bool ok(int x, int y, int dx, int dy) {
    return (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m);
}

void dfs(int x, int y) {
    comp[x][y] = cc;
    for(pair<int, int> d: dir) {
        if(ok(x, y, d.f, d.s) && grid[x][y] == grid[x + d.f][y + d.s] && comp[x + d.f][y + d.s] == -1) {
            dfs(x + d.f, y + d.s);
        }
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    memset(comp, -1, sizeof(comp));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(comp[i][j] == -1) {
                dfs(i, j);
                col[grid[i][j] - '0'].insert(comp[i][j]), ++cc;
            }
            if(i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                border.insert(comp[i][j]);
            }
        }
    }
    FlowNetwork<int> vc(cc + 2);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int id1, id2;
            if(j < m - 1 && comp[i][j] != comp[i][j + 1] && !border.count(comp[i][j]) && !border.count(comp[i][j + 1])) {
                id1 = comp[i][j], id2 = comp[i][j + 1];
                if(grid[i][j] == '1') {
                    swap(id1, id2);
                }
                edges.insert({id1, id2});
            }
            if(i < n - 1 && comp[i][j] != comp[i + 1][j] && !border.count(comp[i][j]) && !border.count(comp[i + 1][j])) {
                id1 = comp[i][j], id2 = comp[i + 1][j];
                if(grid[i][j] == '1') {
                    swap(id1, id2);
                }
                edges.insert({id1, id2});
            }
        }
    }
    for(int c: col[0]) {
        vc.add_edge(0, c + 1, 1);
    }
    for(int c: col[1]) {
        vc.add_edge(c + 1, cc + 1, 1);
    }
    for(pair<int, int> e: edges) {
        vc.add_edge(e.f + 1, e.s + 1, 1);
    }
    cout << vc.dinic_flow(0, cc + 1) + border.size() << endl;
}