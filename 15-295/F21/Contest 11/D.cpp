#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, e, r[300000], front = 1, dep[300000], par[300000][20], up[300000], dest[300000], ans[300000];
vector<int> g[300000];
vector<pair<int, int>> edges;
bool good[300000];

struct DSU {
    int n;
    vector<int> link, sz, up_edge;
 
    DSU(int n): n(n), link(n), sz(n), up_edge(n) {
        for(int i = 0; i < n; i++) {
            link[i] = i;
            sz[i] = 1;
            up_edge[i] = up[i];
        }
    }
 
    int f(int x) {
        return (x == link[x] ? x : link[x] = f(link[x]));
    }
 
    void unite(int x, int y) {
        x = f(x), y = f(y);
        int keep_edge = up_edge[y];
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x, up_edge[x] = keep_edge;
    }
};

void dfs(int u, int p) {
    for(int v: g[u]) {
        if(v != p) {
            dep[v] = dep[u] + 1, par[v][0] = u;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if(dep[u] < dep[v]) {
        swap(u, v);
    }
    for(int i = 19; i >= 0; i--) {
        if((dep[u] - dep[v]) >> i) {
            u = par[u][i];
        }
    }
    for(int i = 19; i >= 0; i--) {
        if(par[u][i] != par[v][i]) {
            u = par[u][i], v = par[v][i];
        }
    }
    return (u == v ? u : par[u][0]);
}

int main() {
    cin >> n >> e;
    for(int i = 0, a, b; i < e; i++) {
        cin >> a >> b;
        edges.push_back({a - 1, b - 1});
    }
    for(int i = 0; i < n - 1; i++) {
        cin >> r[i];
        --r[i], good[r[i]] = true;
        g[edges[r[i]].f].push_back(edges[r[i]].s);
        g[edges[r[i]].s].push_back(edges[r[i]].f);
    }
    dfs(0, 0);
    up[0] = -1;
    for(int i = 0; i < n - 1; i++) {
        if(dep[edges[r[i]].f] < dep[edges[r[i]].s]) {
            swap(edges[r[i]].f, edges[r[i]].s);
        }
        up[edges[r[i]].f] = r[i];
        dest[r[i]] = edges[r[i]].s;
    }
    DSU d(n);
    for(int i = 1; i < 20; i++) {
        for(int j = 0; j < n; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
    for(int i = 0; i < e; i++) {
        if(ans[i] > 0) {
            continue;
        }
        if(good[i]) {
            ans[i] = front++;
            if(dep[edges[i].f] > dep[edges[i].s]) {
                d.unite(edges[i].f, edges[i].s);
            } else {
                d.unite(edges[i].s, edges[i].f);
            }
        } else {
            int u = edges[i].f, v = edges[i].s, l = lca(u, v);
            vector<int> edge;
            while(u > 0) {
                int nxt_edge = d.up_edge[d.f(u)];
                if(dep[dest[nxt_edge]] < dep[l]) {
                    break;
                }
                edge.push_back(nxt_edge);
                u = dest[nxt_edge];
            }
            while(v > 0) {
                int nxt_edge = d.up_edge[d.f(v)];
                if(dep[dest[nxt_edge]] < dep[l]) {
                    break;
                }
                edge.push_back(nxt_edge);
                v = dest[nxt_edge];
            }
            sort(edge.begin(), edge.end());
            for(int e: edge) {
                if(e == -1) {
                    continue;
                }
                ans[e] = front++;
                if(dep[edges[e].f] > dep[edges[e].s]) {
                    d.unite(edges[e].f, edges[e].s);
                } else {
                    d.unite(edges[e].s, edges[e].f);
                }
            }
            ans[i] = front++;
        }
    }
    for(int i = 0; i < e; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}