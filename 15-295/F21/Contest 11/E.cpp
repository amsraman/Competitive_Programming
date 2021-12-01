#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

struct DSU {
    int n;
    vector<int> link, sz, deg;
    vector<bool> good;
 
    DSU(int n): n(n), link(n), sz(n), deg(n, 0), good(n, false) {
        for(int i = 0; i < n; i++) {
            link[i] = i;
            sz[i] = 1;
        }
    }
 
    int f(int x) {
        return (x == link[x] ? x : link[x] = f(link[x]));
    }
 
    void unite(int x, int y) {
        ++deg[x], ++deg[y];
        if(deg[x] >= 3) {
            good[f(x)] = true;
        }
        if(deg[y] >= 3) {
            good[f(y)] = true;
        }
        x = f(x), y = f(y);
        if(x == y) {
            good[x] = true;
        }
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x, good[x] = (good[x] | good[y]);
    }
};

int n, m, q;
pair<int, int> cities[200000], bounds[200000];
array<int, 3> edges[200000];
vector<int> mids[200001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
    }
    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> cities[i].f >> cities[i].s;
        bounds[i] = {0, m};
    }
    sort(edges, edges + m);
    for(int iter = 0; iter < 20; iter++) {
        DSU d(n);
        for(int i = 0; i < q; i++) {
            mids[(bounds[i].f + bounds[i].s) / 2].push_back(i);
        }
        for(int i = 0; i <= m; i++) {
            d.unite(edges[i][1], edges[i][2]);
            for(int j: mids[i]) {
                if(i < m && d.f(cities[j].f) == d.f(cities[j].s) && d.good[d.f(cities[j].f)]) {
                    bounds[j].s = i;
                } else {
                    bounds[j].f = min(bounds[j].s, i + 1);
                }
            }
            mids[i].clear();
        }
    }
    for(int i = 0; i < q; i++) {
        assert(bounds[i].f == bounds[i].s);
        cout << (bounds[i].f == m ? -1 : edges[bounds[i].f][0]) << '\n';
    }
}