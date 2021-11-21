#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 1e15;

int n, m, q, edge_weight[100000];
ll dist[100000], extra[100000];
vector<pair<int, int>> g[100000];
queue<int> dq[100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> q;
    for(int i = 0, a, b, c; i < m; i++) {
        cin >> a >> b >> c;
        edge_weight[i] = c;
        g[a - 1].push_back({b - 1, i});
    }
    for(int j = 1; j < n; j++) {
        dist[j] = INF;
    }
    priority_queue<pair<ll, int>> pq;
    pq.push({0, 0});
    while(!pq.empty()) {
        pair<int, int> tp = pq.top();
        pq.pop();
        if(-tp.f > dist[tp.s]) {
            continue;
        }
        for(pair<int, int> e: g[tp.s]) {
            if(dist[tp.s] + edge_weight[e.s] < dist[e.f]) {
                dist[e.f] = dist[tp.s] + edge_weight[e.s];
                pq.push({-dist[e.f], e.f});
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(pair<int, int> e: g[i]) {
            edge_weight[e.s] += dist[i] - dist[e.f];
        }
    }
    for(int i = 0, tp, v, c; i < q; i++) {
        cin >> tp;
        if(tp == 1) {
            cin >> v;
            cout << (dist[v - 1] >= INF ? -1 : dist[v - 1]) << '\n';
        } else {
            cin >> c;
            for(int j = 0, l; j < c; j++) {
                cin >> l;
                ++edge_weight[l - 1];
            }
            // Dijkstra on Potentials
            for(int j = 1; j < n; j++) {
                extra[j] = INF;
            }
            dq[0].push(0);
            for(int dst = 0; dst <= n; dst++) {
                while(!dq[dst].empty()) {
                    int u = dq[dst].front();
                    dq[dst].pop();
                    if(extra[u] < dst) {
                        continue;
                    }
                    for(pair<int, int> e: g[u]) {
                        if(extra[u] + edge_weight[e.s] < extra[e.f]) {
                            extra[e.f] = extra[u] + edge_weight[e.s];
                            if(extra[e.f] < n) {
                                dq[extra[e.f]].push(e.f);
                            }
                        }
                    }
                }
            }
            for(int i = 0; i < n; i++) {
                dist[i] = min(INF, dist[i] + extra[i]);
                for(pair<int, int> e: g[i]) {
                    edge_weight[e.s] += extra[i] - extra[e.f];
                }
            }
        }
    }
}