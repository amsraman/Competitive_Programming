#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

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

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n;
        cin >> n;
        vector<pair<int, int>> child(n), sweet(n + 1);
        for(int i = 0; i < n; i++) {
            cin >> child[i].f >> child[i].s;
        }
        for(int i = 0; i <= n; i++) {
            cin >> sweet[i].f >> sweet[i].s;
        }
        auto dist = [&](int x, int y) {
            return 1LL * (child[x].f - sweet[y].f) * (child[x].f - sweet[y].f) + 1LL * (child[x].s - sweet[y].s) * (child[x].s - sweet[y].s);
        };
        FlowNetwork<int> match(2 * n + 2);
        for(int i = 0; i < n; i++) {
            match.add_edge(0, i + 1, 1);
            match.add_edge(n + i + 1, 2 * n + 1, 1);
            for(int j = 1; j <= n; j++) {
                if(dist(i, j) <= dist(i, 0)) {
                    match.add_edge(i + 1, j + n, 1);
                }
            }
        }
        int res = match.dinic_flow(0, 2 * n + 1);
        cout << "Case #" << _ << ": ";
        if(res < n) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << "POSSIBLE" << endl;
            vector<int> to(n), from(n), ptr(n, 0);
            vector<bool> used(n, false);
            vector<vector<pair<ll, int>>> closest_ord(n);
            auto nxt = [&](int x) {
                return from[closest_ord[x][ptr[x]].s];
            };
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(match.edge_capacity[j + n + 1][i + 1] == 1) {
                        to[i] = j, from[j] = i;
                    }
                    closest_ord[i].push_back({dist(i, j + 1), j});
                }
                sort(closest_ord[i].begin(), closest_ord[i].end());
            }
            queue<pair<int, int>> closest;
            vector<pair<int, int>> ord;
            for(int i = 0; i < n; i++) {
                if(dist(i, to[i] + 1) == closest_ord[i][0].f) {
                    closest.push({i + 1, to[i] + 1});
                }
            }
            for(int i = 0; i < n; i++) {
                if(closest.empty()) {
                    // Find an even cycle and resolve it
                    int start = 0;
                    while(used[to[start]]) {
                        ++start;
                    }
                    int p1 = start, p2 = nxt(start);
                    while(p1 != p2) {
                        p1 = nxt(p1), p2 = nxt(nxt(p2));
                    }
                    vector<int> cycle;
                    while(true) {
                        cycle.push_back(p2), cycle.push_back(closest_ord[p2][ptr[p2]].s);
                        p2 = nxt(p2);
                        if(p1 == p2) {
                            break;
                        }
                    }
                    for(int j = 0; j < cycle.size(); j += 2) {
                        to[cycle[j]] = cycle[j + 1], from[cycle[j + 1]] = cycle[j];
                    }
                    for(int j = 0; j < n; j++) {
                        if(!used[to[j]] && dist(j, to[j] + 1) == closest_ord[j][ptr[j]].f) {
                            closest.push({j + 1, to[j] + 1});
                        }
                    }
                }
                assert(!closest.empty());
                ord.push_back(closest.front()), used[closest.front().s - 1] = true;
                closest.pop();
                for(int j = 0; j < n; j++) {
                    while(ptr[j] < n && used[closest_ord[j][ptr[j]].s]) {
                        ++ptr[j];
                    }
                }
            }
            for(pair<int, int> o: ord) {
                cout << o.f << " " << o.s + 1 << endl;
            }
        }
    }
}