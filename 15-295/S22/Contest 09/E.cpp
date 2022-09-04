#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <typename T>
struct FlowNetwork {
    size_t n;
    T INF = numeric_limits<T>::max();
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

const ll INF = 0xffffffffffffff;

int n, m, s, b, k;
ll dist[100][100], bit[100][100], ans;
array<int, 5> spaceships[100000];
array<int, 3> bases[100000];
set<int> best_price[100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) {
                dist[i][j] = INF;
            }
            bit[i][j] = -INF;
        }
    }
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        if(u != v) {
            dist[u - 1][v - 1] = dist[v - 1][u - 1] = 1;
        }
    }
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    cin >> s >> b >> k;
    for(int i = 0; i < s; i++) {
        cin >> spaceships[i][1] >> spaceships[i][0] >> spaceships[i][2] >> spaceships[i][3];
        spaceships[i][4] = i;
    }
    for(int i = 0; i < b; i++) {
        cin >> bases[i][1] >> bases[i][0] >> bases[i][2];
    }
    sort(spaceships, spaceships + s);
    sort(bases, bases + b);
    FlowNetwork<ll> cut(s + 2);
    for(int i = 0, j = 0; i < s; i++) {
        // For each spaceship, find the best base to attack
        while(j < b && bases[j][0] <= spaceships[i][0]) {
            int loc = bases[j][1] - 1;
            for(int d = 0; d < n; d++) {
                for(ll x = dist[d][loc] + 1; x <= n; x += x & -x) {
                    bit[d][x - 1] = max(bit[d][x - 1], 1LL * bases[j][2]);
                }
            }
            ++j;
        }
        int loc = spaceships[i][1] - 1;
        ll best = -INF;
        for(ll x = min(n, spaceships[i][2] + 1); x > 0; x -= x & -x) {
            best = max(best, bit[loc][x - 1]);
        }
        best -= spaceships[i][3];
        ans += max(best, 0LL);
        if(best > 0) {
            cut.add_edge(0, spaceships[i][4] + 1, best);
        } else if(best < 0) {
            cut.add_edge(spaceships[i][4] + 1, s + 1, -best);
        }
    }
    for(int i = 0, s1, s2; i < k; i++) {
        cin >> s1 >> s2;
        cut.add_edge(s1, s2, cut.INF);
    }
    cout << ans - cut.dinic_flow(0, s + 1) << '\n';
}