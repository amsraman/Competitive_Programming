#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, q, dep[300000], par[300000][19], mn[300000][19];
vector<pair<int, int>> g[300000];

void dfs(int x, int p) {
    for(pair<int, int> e: g[x]) {
        if(e.f != p) {
            par[e.f][0] = x;
            mn[e.f][0] = e.s;
            dep[e.f] = dep[x] + 1;
            dfs(e.f, x);
        }
    }
}

int get_min(int u, int v) {
    int ret = INF;
    if(dep[v] > dep[u]) {
        swap(u, v);
    }
    for(int i = 18, d = dep[u] - dep[v]; i >= 0; i--) {
        if((d >> i) & 1) {
            ret = min(ret, mn[u][i]);
            u = par[u][i];
        }
    }
    for(int i = 18; i >= 0; i--) {
        if(par[u][i] != par[v][i]) {
            ret = min({ret, mn[u][i], mn[v][i]});
            u = par[u][i];
            v = par[v][i];
        }
    }
    return (u == v ? ret : min({ret, mn[u][0], mn[v][0]}));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    assert(m == n - 1);
    for(int i = 0, u, v, w; i < n - 1; i++) {
        cin >> u >> v >> w;
        g[u - 1].push_back({v - 1, w});
        g[v - 1].push_back({u - 1, w});
    }
    dfs(0, 0);
    for(int i = 1; i < 19; i++) {
        for(int j = 0; j < n; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
            mn[j][i] = min(mn[j][i - 1], mn[par[j][i - 1]][i - 1]);
        }
    }
    cin >> q;
    for(int i = 0, a, b; i < q; i++) {
        cin >> a >> b;
        cout << get_min(a - 1, b - 1) << '\n';
    }
}