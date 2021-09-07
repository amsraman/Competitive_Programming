#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 2e18;

int n, m, d, cur, lst[200000], num[200000];
ll times[200000], dist[200000][2];
vector<int> stops;
vector<pair<int, int>> g[200000];
bool vis[200000][2];

void solve() {
    for(int i = 1; i < n; i++) {
        dist[i][0] = dist[i][1] = INF;
    }
    priority_queue<pair<ll, int>> q;
    q.push({0, 0});
    while(!q.empty()) {
        int v = q.top().s;
        q.pop();
        if(vis[v][0]) {
            continue;
        }
        vis[v][0] = true;
        for(pair<int, int> e: g[v]) {
            if(!vis[e.f][0] && dist[v][0] + e.s < dist[e.f][0]) {
                dist[e.f][0] = dist[v][0] + e.s;
                q.push({-dist[e.f][0], e.f});
            }
        }
    }
    q.push({0, 0});
    num[0] = 1;
    while(!q.empty()) {
        int v = q.top().s;
        q.pop();
        if(vis[v][1]) {
            continue;
        }
        vis[v][1] = true;
        if(cur < d && times[cur] == dist[v][1]) {
            ++cur;
        }
        for(pair<int, int> e: g[v]) {
            if(!vis[e.f][1] && dist[v][1] + e.s <= dist[e.f][1] && (cur == d || dist[v][1] + e.s <= times[cur])) {
                if(dist[v][1] + e.s == dist[e.f][1]) {
                    num[e.f] = min(2, num[e.f] + num[v]);
                } else {
                    num[e.f] = num[v];
                }
                dist[e.f][1] = dist[v][1] + e.s;
                lst[e.f] = v;
                q.push({-dist[e.f][1], e.f});
            }
        }
    }
    if(dist[n - 1][0] != dist[n - 1][1] || cur < d || times[d - 1] > dist[n - 1][0]) {
        cout << 0 << endl;
        return;
    }
    if(num[n - 1] == 2) {
        cout << 1 << endl;
        return;
    }
    int lst_vertex = n - 1;
    stops.push_back(n - 1);
    while(lst_vertex > 0) {
        lst_vertex = lst[lst_vertex];
        stops.push_back(lst_vertex);
    }
    reverse(stops.begin(), stops.end());
    cout << stops.size() << endl;
    for(int i: stops) {
        cout << i + 1 << endl;
    }
}

int main() {
    cin >> n >> m >> d;
    for(int i = 0, u, v, h; i < m; i++) {
        cin >> u >> v >> h;
        g[u - 1].push_back({v - 1, h});
    }
    for(int i = 0; i < d; i++) {
        cin >> times[i];
    }
    sort(times, times + d);
    solve();
}