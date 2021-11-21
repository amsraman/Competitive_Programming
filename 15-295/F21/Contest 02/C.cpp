#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 0xffffffffff;

int n, m, x, y, t[1000], c[1000];
ll dist[1000][1000], fdist[1000];
vector<pair<int, int>> g[1000];

void djk(int v) {
    for(int i = 0; i < n; i++) {
        dist[v][i] = INF;
    }
    dist[v][v] = 0;
    priority_queue<pair<ll, int>> q;
    q.push({0, v});
    while(!q.empty()) {
        int vv = q.top().s;
        ll d = -q.top().f;
        q.pop();
        if(d > dist[v][vv]) {
            continue;
        }
        for(pair<int, int> e: g[vv]) {
            if(dist[v][vv] + e.s < dist[v][e.f]) {
                dist[v][e.f] = dist[v][vv] + e.s;
                q.push({-dist[v][e.f], e.f});
            }
        }
    }
}

int main() {
    cin >> n >> m >> x >> y;
    for(int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        g[u - 1].push_back({v - 1, w});
        g[v - 1].push_back({u - 1, w});
    }
    for(int i = 0; i < n; i++) {
        cin >> t[i] >> c[i];
    }
    for(int i = 0; i < n; i++) {
        djk(i);
    }
    priority_queue<pair<ll, int>> q;
    for(int i = 0; i < n; i++) {
        fdist[i] = INF;
    }
    fdist[x - 1] = 0;
    q.push({0, x - 1});
    while(!q.empty()) {
        int v = q.top().s;
        ll d = -q.top().f;
        q.pop();
        if(d > fdist[v]) {
            continue;
        }
        for(int i = 0; i < n; i++) {
            if(dist[v][i] <= t[v] && fdist[v] + c[v] < fdist[i]) {
                fdist[i] = fdist[v] + c[v];
                q.push({-fdist[i], i});
            }
        }
    }
    cout << (fdist[y - 1] == INF ? -1 : fdist[y - 1]) << endl;
}