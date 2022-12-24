#include <bits/stdc++.h>
typedef long double ld;

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

const ld eps = 1e-15, PI = acosl(-1);

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int m, n; cin >> m >> n;
    vector<array<int, 2>> points(m), rays(n);
    vector<int> v(n);
    for(int i = 0; i < m; i++) {
        cin >> points[i][0] >> points[i][1];
    }
    for(int i = 0; i < n; i++) {
        cin >> rays[i][0] >> rays[i][1] >> v[i];
    }
    FlowNetwork<int> fn(n + m + 2);
    for(int i = 0; i < n; i++) {
        fn.add_edge(0, i + 1, v[i]);
    }
    vector<int> ray_ord(n); iota(ray_ord.begin(), ray_ord.end(), 0);
    auto get_ang = [](array<int, 2> pt) {
        ld res = atan2l(pt[1], pt[0]);
        if(res < 0) res += 2 * PI;
        return res;
    };
    sort(ray_ord.begin(), ray_ord.end(), [&](int x, int y) {
        return get_ang(rays[x]) < get_ang(rays[y]);
    });
    for(int i = 0; i < m; i++) {
        ld cur_ang = get_ang(points[i]);
        int ind = lower_bound(ray_ord.begin(), ray_ord.end(), cur_ang, [&](int x, ld ang) {
            return get_ang(rays[x]) < ang;
        }) - ray_ord.begin();
        ind = (ind + n - 1) % n;
        ld diff1 = cur_ang - get_ang(rays[ray_ord[ind]]), diff2 = get_ang(rays[ray_ord[(ind + 1) % n]]) - cur_ang;
        if(diff1 < 0) diff1 += 2 * PI;
        if(diff2 < 0) diff2 += 2 * PI;
        if(diff1 <= diff2 + eps) {
            fn.add_edge(ray_ord[ind] + 1, i + n + 1, 1);
        }
        if(diff2 <= diff1 + eps) {
            fn.add_edge(ray_ord[(ind + 1) % n] + 1, i + n + 1, 1);
        }
        fn.add_edge(i + n + 1, n + m + 1, 1);
    }
    cout << fn.dinic_flow(0, n + m + 1) << '\n';
    for(int i = 0; i < m; i++) {
        for(int j: fn.graph[i + n + 1]) {
            if(fn.edge_capacity[i + n + 1][j] == 1 && j != n + m + 1) {
                cout << i << " " << j - 1 << '\n';
            }
        }
    }
}