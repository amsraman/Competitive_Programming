#include <bits/stdc++.h>
typedef __int128_t ll;

using namespace std;

void EnumerateTriangles(vector<vector<pair<int, int>>> & graph, function<void (int, int, int, int, int, int)> f) {
    int n = graph.size();
    vector<vector<pair<int, int>>> bigger_neighbors(n);
    for(int i = 0; i < n; i++) {
        for(pair<int, int> j: graph[i]) {
            if(graph[j.first].size() > graph[i].size() || (graph[j.first].size() == graph[i].size() && j.first > i)) {
                bigger_neighbors[i].push_back(j);
            }
        }
    }
    vector<int> neighbor(n, -1);
    for(int i = 0; i < n; i++) {
        for(pair<int, int> j: bigger_neighbors[i]) neighbor[j.first] = j.second;
        for(pair<int, int> j: bigger_neighbors[i]) {
            for(pair<int, int> k: bigger_neighbors[j.first]) {
                if(neighbor[k.first] >= 0) {
                    f(i, j.first, k.first, j.second, k.second, neighbor[k.first]);
                }
            }
        }
        for(pair<int, int> j: bigger_neighbors[i]) neighbor[j.first] = -1;
    }
}

template <typename T>
T CountFourCycles(const vector<vector<pair<int, int>>> & graph) {
    int n = graph.size();
    T ans = 0;
    vector<pair<int, int>> deg_pair(n);
    for(int i = 0; i < n; i++) deg_pair[i] = {graph[i].size(), i};
    vector<vector<int>> bigger_neighbors(n);
    for(int i = 0; i < n; i++) {
        for(pair<int, int> j: graph[i]) {
            if(deg_pair[j.first] > deg_pair[i]) {
                bigger_neighbors[i].push_back(j.first);
            }
        }
    }
    vector<T> two_paths(n, 0);
    for(int i = 0; i < n; i++) {
        for(pair<int, int> j: graph[i]) {
            for(int k: bigger_neighbors[j.first]) {
                if(deg_pair[k] > deg_pair[i]) {
                    ans += two_paths[k]++;
                }
            }
        }
        for(pair<int, int> j: graph[i]) {
            for(int k: bigger_neighbors[j.first]) {
                two_paths[k] = 0;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    vector<int> edge_tris(m);
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u - 1].push_back({v - 1, i});
        g[v - 1].push_back({u - 1, i});
    }
    ll ans = (ll) n * (n - 1) * (n - 2) * (n - 3) / 24;
    ans -= (ll) m * (n - 2) * (n - 3) / 2;
    ans += (ll) m * (m - 1) / 2;
    for(int i = 0; i < n; i++) {
        ans += (ll) g[i].size() * (g[i].size() - 1) * (n - 4) / 2;
        ans -= (ll) g[i].size() * (g[i].size() - 1) * (g[i].size() - 2) / 6;
        for(pair<int, int> j: g[i]) {
            if(i > j.first) {
                ans -= (ll) (g[i].size() - 1) * (g[j.first].size() - 1);
            }
        }
    }
    auto f = [&](int x, int y, int z, int a, int b, int c) {
        ans -= n - 6;
        ans += g[x].size() + g[y].size() + g[z].size() - 6;
        ans -= edge_tris[a]++; ans -= edge_tris[b]++; ans -= edge_tris[c]++;
    };
    EnumerateTriangles(g, f);
    ans += CountFourCycles<ll>(g);
    ans = max(ans, -ans);
    vector<int> dig; // how to print 128 bit ints ._.
    if(ans == 0) dig.push_back(0);
    while(ans) {
        dig.push_back(ans % 10);
        ans /= 10;
    }
    reverse(dig.begin(), dig.end());
    for(int d: dig) {
        cout << d;
    }
    cout << '\n';
}