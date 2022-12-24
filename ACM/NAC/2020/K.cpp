#include <bits/stdc++.h>

using namespace std;

int n, q, par[200000][18], dep[200000];
vector<int> g[200000];

void dfs(int u, int p) {
    for(int i = 1; i < 18; i++) {
        par[u][i] = par[par[u][i - 1]][i - 1];
    }
    for(int v: g[u]) {
        if(v != p) {
            dep[v] = dep[u] + 1, par[v][0] = u, dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 17; i >= 0; i--) {
        if((dep[u] - dep[v]) >> i) {
            u = par[u][i];
        }
    }
    for(int i = 17; i >= 0; i--) {
        if(par[u][i] != par[v][i]) {
            u = par[u][i], v = par[v][i];
        }
    }
    return (u == v ? u : par[u][0]);
}

int dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs(0, 0);
    for(int i = 0, r, p; i < q; i++) {
        cin >> r >> p;
        int len = dist(r - 1, p - 1) + 1;
        cout << 1LL * len * (len + 1) / 2 + n - len << '\n';
    }
}