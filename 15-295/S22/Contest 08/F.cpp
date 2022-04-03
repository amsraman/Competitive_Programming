#include <bits/stdc++.h>
typedef long double ld;
#define f first
#define s second

using namespace std;

int n, m, deg[300000];
ld sum[300000], ev[300000];
vector<int> g[300000];
bool vis[300000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    priority_queue<pair<ld, int>> q;
    q.push({0.0, n - 1});
    while(!q.empty()) {
        pair<ld, int> tp = q.top();
        q.pop();
        int u = tp.s;
        if(vis[u]) {
            continue;
        }
        vis[u] = true;
        for(int v: g[u]) {
            if(!vis[v]) {
                ++deg[v];
                sum[v] += ev[u];
                ev[v] = (sum[v] + (ld) g[v].size()) / deg[v];
                q.push({-ev[v], v});
            }
        }
    }
    cout << fixed << setprecision(9) << ev[0] << '\n';
}