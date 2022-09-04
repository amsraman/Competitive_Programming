#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

int n, fact[300001], ifact[300001], up[300000], sat[300000], ans[300000];
vector<int> g[300000];
vector<pair<int, int>> edges[300001];
set<int> roots;

struct DSU {
    int n;
    vector<int> link, sz;

    DSU(int n): n(n), link(n), sz(n, 1) {
        for(int i = 0; i < n; i++) {
            link[i] = i;
            if(g[i].size() != 2) {
                roots.insert(i);
            }
        }
    }

    int f(int x) {
        return (x == link[x] ? x : link[x] = f(link[x]));
    }

    void unite(int x, int y) {
        x = f(x), y = f(y);
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x, roots.erase(y);
        sat[x] += sat[y] - 2;
    }
};

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret = mul(ret, x);
        }
        x = mul(x, x), y >>= 1;
    }
    return ret;
}

int dfs(int x, int p, int d) {
    up[x] = (g[p].size() == 2 ? up[p] : d - 1);
    int down;
    for(int u: g[x]) {
        if(u != p) {
            down = dfs(u, x, d + 1);
        }
    }
    if(g[x].size() != 2) {
        down = d;
    }
    if(x != p && n - down + up[x] - 2 >= 0) {
        edges[n - down + up[x] - 2].push_back({x, p});
    }
    return down;
}

int main() {
    ifstream cin("circus.in");
    ofstream cout("circus.out");
    cin >> n;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
        ++sat[u - 1], ++sat[v - 1];
    }
    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
    ifact[n] = exp(fact[n], mod - 2);
    for(int i = n - 1; i >= 0; i--) {
        ifact[i] = mul(ifact[i + 1], i + 1);
    }
    int root = 0;
    while(g[root].size() == 2) {
        ++root;
    }
    dfs(root, root, 0);
    DSU d(n);
    ans[n - 1] = fact[n];
    for(int i = n - 1; i > 0; i--) {
        for(pair<int, int> e: edges[i]) {
            d.unite(e.f, e.s);
        }
        ans[i - 1] = fact[i];
        for(int r: roots) {
            ans[i - 1] = mul(ans[i - 1], ifact[(n - i - 1) * (sat[r] - 1) + d.sz[r] - 1]);
        }
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
}