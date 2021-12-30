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

int t, n, m, x, y, sz, del_x[1200], del_y[1200], ans1[300], ans2[300];
pair<int, int> lec[300], sem[300];
map<int, int> ind;
set<int> coords;
bool pos;

int main() {
    cin >> t;
    while(t--) {
        cin >> n >> m >> x >> y;
        for(int i = 0; i < n; i++) {
            cin >> lec[i].f >> lec[i].s;
            coords.insert(lec[i].f), coords.insert(lec[i].s);
        }
        for(int i = 0; i < m; i++) {
            cin >> sem[i].f >> sem[i].s;
            coords.insert(sem[i].f), coords.insert(sem[i].s);
        }
        pos = true, sz = 0;
        memset(del_x, 0, sizeof(del_x)), memset(del_y, 0, sizeof(del_y));
        for(int i: coords) {
            ind[i] = sz++;
        }
        FlowNetwork<int> non_hd(sz + 2);
        for(int i = 0; i < n; i++) {
            lec[i].f = ind[lec[i].f], lec[i].s = ind[lec[i].s];
            ++del_x[lec[i].f], --del_x[lec[i].s];
        }
        for(int i = 0; i < m; i++) {
            sem[i].f = ind[sem[i].f], sem[i].s = ind[sem[i].s];
            ++del_y[sem[i].f], --del_y[sem[i].s];
            non_hd.add_edge(sem[i].f + 1, sem[i].s + 1, 1);
        }
        non_hd.add_edge(0, 1, y);
        int cur_x = 0, cur_y = 0;
        for(int i = 0; i < sz; i++) {
            cur_x += del_x[i], cur_y += del_y[i];
            if(cur_x > x || cur_x + cur_y > x + y) {
                pos = false;
            }
            non_hd.add_edge(i + 1, i + 2, min(y, x + y - cur_x - cur_y));
        }
        if(pos) {
            pos &= (non_hd.dinic_flow(0, sz + 1) == y);
        }
        if(!pos) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            vector<pair<int, int>> ev1, ev2;
            queue<int> q1, q2;
            // Greedy Assignment for Non-HD
            for(int i = 0; i < y; i++) {
                q1.push(x + i + 1);
            }
            for(int i = 0; i < m; i++) {
                if(non_hd.edge_capacity[sem[i].s + 1][sem[i].f + 1] > 0) {
                    ev1.push_back({(sem[i].f << 1) | 1, i});
                    ev1.push_back({sem[i].s << 1, i});
                    --non_hd.edge_capacity[sem[i].s + 1][sem[i].f + 1];
                } else {
                    ev2.push_back({(sem[i].f << 1) | 1, (i << 1) | 1});
                    ev2.push_back({sem[i].s << 1, (i << 1) | 1});
                }
            }
            sort(ev1.begin(), ev1.end());
            for(pair<int, int> e: ev1) {
                if(e.f & 1) {
                    ans2[e.s] = q1.front();
                    q1.pop();
                } else {
                    q1.push(ans2[e.s]);
                }
            }
            // Greedy Assignment for HD
            for(int i = 0; i < x; i++) {
                q2.push(i + 1);
            }
            for(int i = 0; i < n; i++) {
                ev2.push_back({(lec[i].f << 1) | 1, i << 1});
                ev2.push_back({(lec[i].s << 1), i << 1});
            }
            sort(ev2.begin(), ev2.end());
            for(pair<int, int> e: ev2) {
                if(e.f & 1) {
                    if(e.s & 1) {
                        ans2[e.s >> 1] = q2.front();
                    } else {
                        ans1[e.s >> 1] = q2.front();
                    }
                    q2.pop();
                } else {
                    int cur = ((e.s & 1) ? ans2[e.s >> 1] : ans1[e.s >> 1]);
                    q2.push(cur);
                }
            }
            for(int i = 0; i < n; i++) {
                cout << ans1[i] << " ";
            }
            for(int i = 0; i < m; i++) {
                cout << ans2[i] << " ";
            }
            cout << '\n';
        }
        coords.clear(), ind.clear();
    }
}
