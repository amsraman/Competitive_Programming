// 333 ms
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <typename T>
vector<pair<T, int>> Dijkstra(vector<vector<pair<int, T>>> & graph, int s) {
    // Returns (distance, parent) pairs
    int n = graph.size();
    T INF = numeric_limits<T>::max();
    vector<pair<T, int>> dist(n, {INF, -1});
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
    q.push({0, s}), dist[s] = {0, -1};
    while(!q.empty()) {
        pair<T, int> tp = q.top(); q.pop();
        if(tp.first > dist[tp.second].first) {
            continue;
        }
        int u = tp.second;
        for(pair<int, T> e: graph[u]) {
            if(dist[u].first + e.second < dist[e.first].first) {
                dist[e.first] = {dist[u].first + e.second, u};
                q.push({dist[e.first].first, e.first});
            }
        }
    }
    return dist;
}

const ll INF = numeric_limits<ll>::max();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<pair<int, ll>>> g(n);
    for(int i = 0, a, b, c; i < m; i++) {
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }
    vector<pair<ll, int>> dist = Dijkstra(g, s);
    if(dist[t].first == INF) {
        cout << "-1\n";
    } else {
        vector<int> path;
        int cur = t;
        path.push_back(t);
        while(cur != s) {
            cur = dist[cur].second, path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        cout << dist[t].first << " " << path.size() - 1 << '\n';
        for(int i = 0; i + 1 < path.size(); i++) {
            cout << path[i] << " " << path[i + 1] << '\n';
        }
    }
}