#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, m, deg[100000];
ll ans;
vector<int> g[100000];
vector<pair<int, int>> edges;
unordered_set<int> es[100000];
bool vis[100000];

ll choose2(int x) {
    if(x < 2) {
        return 0;
    }
    return (ll) x * (x - 1) / 2;
}

ll choose3(int x) {
    if(x < 3) {
        return 0;
    }
    return (ll) x * (x - 1) * (x - 2) / 6;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
        ++deg[u - 1], ++deg[v - 1];
        edges.push_back({u - 1, v - 1});
        es[u - 1].insert(v - 1), es[v - 1].insert(u - 1);
    }
    for(int i = 0; i < n; i++) {
        for(int j: g[i]) {
            if(deg[j] >= 4) {
                ans += choose3(deg[j] - 1) * (deg[i] - 1);
            }
        }
    }
    for(pair<int, int> e: edges) {
        if(deg[e.f] > deg[e.s]) {
            swap(e.f, e.s);
        }
        for(int j: g[e.f]) {
            if(es[j].count(e.s)) {
                ans -= choose2(deg[j] - 2) * 2;
            }
        }
    }
    cout << ans << '\n';
}