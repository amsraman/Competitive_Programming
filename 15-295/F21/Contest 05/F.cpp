#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, w[200000], p[200000];
ll lft[200000], wt[200000], dem[200000], total_weight[200000];
pair<int, int> edg[200000];
vector<pair<int, int>> g[200000];
bool ans = true;

void dfs1(int u, int cur_edge) {
    for(pair<int, int> e: g[u]) {
        if(e.s != cur_edge) {
            dfs1(e.f, e.s);
            lft[u] += lft[e.f];
            wt[u] += wt[e.f];
        }
    }
    if(cur_edge != -1) {
        ll help = max(0LL, min(lft[u], wt[u] - p[cur_edge]));
        dem[u] = help, lft[u] -= help, wt[u] -= help;
        if(p[cur_edge] < wt[u]) {
            ans = false;
        }
        lft[u] += min(p[cur_edge], w[cur_edge] - 1);
        wt[u] += w[cur_edge];
    }
}

ll dfs2(int u, int cur_edge, ll need) {
    need += dem[u];
    for(pair<int, int> e: g[u]) {
        if(e.s != cur_edge) {
            need = dfs2(e.f, e.s, need);
            total_weight[u] += total_weight[e.f];
        }
    }
    if(cur_edge != -1) {
        int pos = max(0LL, min({need, (ll) w[cur_edge] - 1, (ll) p[cur_edge] - total_weight[u]}));
        w[cur_edge] -= pos, p[cur_edge] -= pos, need -= pos;
    }
    total_weight[u] += w[cur_edge];
    return need;
}

int main() {
    cin >> n;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v >> w[i] >> p[i];
        g[u - 1].push_back({v - 1, i});
        g[v - 1].push_back({u - 1, i});
        edg[i] = {u, v};
    }
    dfs1(0, -1);
    if(ans) {
        cout << n << endl;
        assert(dfs2(0, -1, 0) == 0);
        for(int i = 0; i < n - 1; i++) {
            cout << edg[i].f << " " << edg[i].s << " " << w[i] << " " << p[i] << endl;
        }
    } else {
        cout << -1 << endl;
    }
}