// 340 ms
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 0xfffffffffffffff;

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
    vector<int> pv(n, -1), path;
    vector<ll> dist(n, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.push({0, s}), dist[s] = 0;
    while(!q.empty()) {
        pair<ll, int> tp = q.top(); q.pop();
        if(tp.first > dist[tp.second]) {
            continue;
        }
        int u = tp.second;
        for(pair<int, ll> e: g[u]) {
            if(dist[u] + e.second < dist[e.first]) {
                dist[e.first] = dist[u] + e.second, pv[e.first] = u;
                q.push({dist[e.first], e.first});
            }
        }
    }
    if(dist[t] == INF) {
        cout << "-1\n";
    } else {
        int cur = t;
        path.push_back(t);
        while(cur != s) {
            cur = pv[cur], path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        cout << dist[t] << " " << path.size() - 1 << '\n';
        for(int i = 0; i + 1 < path.size(); i++) {
            cout << path[i] << " " << path[i + 1] << '\n';
        }
    }
}