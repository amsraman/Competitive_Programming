#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 1e18;

int n, m, k, num[100000], ans;
ll dist[100000];
vector<pair<int, int>> trains;
vector<pair<int, int>> g[100000];
bool vis[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    for(int i = 0, u, v, x; i < m; i++) {
        cin >> u >> v >> x;
        g[u - 1].push_back({v - 1, x});
        g[v - 1].push_back({u - 1, x});
    }
    set<pair<int, int>> exists;
    for(int i = 0, s, y; i < k; i++) {
        cin >> s >> y;
        if(exists.count({s, y})) {
            continue;
        }
        exists.insert({s, y});
        g[0].push_back({s - 1, y});
        trains.push_back({s - 1, y});
    }
    priority_queue<pair<ll, int>> q;
    q.push({0, 0});
    for(int i = 1; i < n; i++) {
        dist[i] = INF;
    }
    while(!q.empty()) {
        pair<ll, int> tp = q.top();
        q.pop();
        if(vis[tp.s]) {
            continue;
        }
        if(-tp.s > dist[tp.s]) {
            continue;
        }
        vis[tp.s] = true;
        for(pair<int, int> e: g[tp.s]) {
            if(-tp.f + e.s < dist[e.f]) {
                dist[e.f] = -tp.f + e.s;
                q.push({tp.f - e.s, e.f});
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(pair<int, int> e: g[i]) {
            if(dist[i] + e.s == dist[e.f]) {
                ++num[e.f];
            }
        }
    }
    for(pair<int, int> t: trains) {
        if(num[t.f] == 1 && t.s == dist[t.f]) {
            ++ans;
        }
    }
    cout << k - ans << '\n';
}