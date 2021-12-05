#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, k, q, ec, ans[100000];
vector<pair<int, int>> edges;
vector<int> edge_ids[100000];
bool gone[100000];

struct DSU {
    int n;
    vector<int> link, sz, redir;
 
    DSU(int n): n(n), link(n), sz(n), redir(n) {
        for(int i = 0; i < n; i++) {
            link[i] = redir[i] = i;
            sz[i] = 1;
        }
    }
 
    int f(int x) {
        return (x == link[x] ? x : link[x] = f(link[x]));
    }

    void add_edge(int x, int y) {
        edges.push_back({x, y});
        int edge_id = ec++, rdrx = redir[f(x)], rdry = redir[f(y)];
        if (rdrx != rdry) {
            edge_ids[rdrx].push_back(edge_id);
            edge_ids[rdry].push_back(edge_id);
        } else {
            ++ans[x], ++ans[y];
        }
    }

    void merge(int x, int y) {
        // Merge y into x
        int rdrx = redir[x], rdry = redir[y];
        assert(!gone[rdrx] && !gone[rdry]);
        for(int e: edge_ids[rdry]) {
            int u = edges[e].f, v = edges[e].s, fu = f(u), fv = f(v);
            if(fu == fv) {
                continue;
            } else if((fu == x && fv == y) || (fu == y && fv == x)) {
                ++ans[u], ++ans[v];
            } else {
                edge_ids[rdrx].push_back(e);
            }
        }
        gone[rdry] = true;
        edge_ids[rdry].clear();
    }
 
    void unite(int x, int y) {
        x = f(x), y = f(y);
        if(x == y) {
            return;
        }
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        if(edge_ids[redir[x]].size() < edge_ids[redir[y]].size()) {
            swap(redir[x], redir[y]);
        }
        merge(x, y);
        sz[x] += sz[y], link[y] = x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    DSU d(n);
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        d.add_edge(u - 1, v - 1);
    }
    for(int i = 0, u, v; i < k; i++) {
        cin >> u >> v;
        d.unite(u - 1, v - 1);
    }
    cin >> q;
    for(int i = 0; i < q; i++) {
        char tp;
        cin >> tp;
        if(tp == 'F') {
            int a, b;
            cin >> a >> b;
            d.add_edge(a - 1, b - 1);
        } else if(tp == 'T') {
            int a, b;
            cin >> a >> b;
            d.unite(a - 1, b - 1);
        } else {
            int v;
            cin >> v;
            cout << ans[v - 1] << '\n';
        }
    }
}