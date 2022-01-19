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

int n, m, cc, id[100][100], df[10000], sz[10000], par[10000], tot;
pair<int, int> dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
string a[100], b[100];
set<pair<int, int>> edges;
bool vis[100][100];

bool ok(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void dfs(int x, int y) {
    vis[x][y] = true;
    ++sz[cc], df[cc] += (a[x][y] != b[x][y]), par[cc] = (a[x][y] == '1'), id[x][y] = cc;
    for(pair<int, int> d: dir) {
        if(ok(x + d.f, y + d.s) && !vis[x + d.f][y + d.s] && a[x + d.f][y + d.s] == a[x][y]) {
            dfs(x + d.f, y + d.s);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(!vis[i][j]) {
                dfs(i, j);
                cc++;
            }
        }
    }
    FlowNetwork<int> net(cc + 2);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i < n - 1 && a[i][j] != a[i + 1][j]) {
                int id1 = id[i][j], id2 = id[i + 1][j];
                if(par[id2]) {
                    swap(id1, id2);
                }
                edges.insert({id1, id2});
            }
            if(j < m - 1 && a[i][j] != a[i][j + 1]) {
                int id1 = id[i][j], id2 = id[i][j + 1];
                if(par[id2]) {
                    swap(id1, id2);
                }
                edges.insert({id1, id2});
            }
            tot += (a[i][j] == b[i][j]);
        }
    }
    int tot_w = 0;
    for(int i = 0; i < cc; i++) {
        if(par[i]) {
            net.add_edge(0, i + 1, max(0, 2 * df[i] - sz[i]));
        } else {
            net.add_edge(i + 1, cc + 1, max(0, 2 * df[i] - sz[i]));
        }
        tot_w += max(0, 2 * df[i] - sz[i]);
    }
    for(pair<int, int> e: edges) {
        net.add_edge(e.f + 1, e.s + 1, 0x3f3f3f3f);
    }
    int vc = net.dinic_flow(0, cc + 1), is = tot_w - vc;
    cout << n * m - tot - is << '\n';
}