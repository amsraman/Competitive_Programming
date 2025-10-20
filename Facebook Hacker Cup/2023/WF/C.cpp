#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

struct DSU {
    int n; vector<int> link, sz, mx; vector<ll> sum;
    DSU(int n): n(n), link(n), sz(n, 1), mx(n), sum(n) {
        iota(link.begin(), link.end(), 0);
        iota(mx.begin(), mx.end(), 0);
    }
    int find(int x) {
        return (x == link[x] ? x : link[x] = find(link[x]));
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x, sum[x] += sum[y], mx[x] = max(mx[x], mx[y]);
    }
};

int main() {
    ifstream cin("resisting_robots_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m; cin >> n >> m;
        vector<ll> p(n); vector<pair<ll, int>> srt;
        for(int i = 0; i < n; i++) {
            cin >> p[i]; srt.emplace_back(p[i], i);
        }
        sort(srt.begin(), srt.end()); vector<int> ind(n);
        for(int i = 0; i < n; i++) ind[srt[i].second] = i;
        sort(p.begin(), p.end());
        vector<vector<int>> g(n);
        for(int i = 0, a, b; i < m; i++) {
            cin >> a >> b; a = ind[a - 1], b = ind[b - 1];
            if(a > b) swap(a, b);
            g[b].push_back(a);
        }
        DSU d(n); vector<vector<pair<int, ll>>> tr(n);
        for(int i = 0; i < n; i++) d.sum[i] = p[i];
        for(int u = 0; u < n; u++) {
            for(int v: g[u]) {
                if(d.find(u) == d.find(v)) continue;
                v = d.find(v); tr[u].emplace_back(d.mx[v], max(0LL, p[u] - d.sum[v]));
                d.unite(u, v);
            }
        }
        vector<ll> ans(n, 0); ll res = 0;
        for(int u = n - 1; u >= 0; u--) {
            for(auto [v, w]: tr[u]) {
                ans[v] = max(ans[u], w);
            }
            res += ans[u];
        }
        cout << "Case #" << _ << ": " << res << '\n';
    }
}
