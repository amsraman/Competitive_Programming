#include <bits/stdc++.h>
#include <sys/resource.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

struct DSU {
    int n;
    vector<int> link, sz;

    DSU(int n): n(n), link(n), sz(n) {
        for(int i = 0; i < n; i++) {
            link[i] = i;
            sz[i] = 1;
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
        sz[x] += sz[y], link[y] = x;
    }
};

int t, n, pairs[800000];
array<int, 21> mx[800000], from_top[800000];
vector<pair<int, int>> g[800000];

int mul(int a, int b) {
    return ((ll) a * b) % mod;
}

void dfs(int x, int p) {
    mx[x].fill(0);
    for(pair<int, int> e: g[x]) {
        if(e.f != p) {
            dfs(e.f, x);
            for(int i = 0; i <= 20; i++) {
                mx[x][min(i, e.s)] += mx[e.f][i];
            }
            mx[x][e.s]++;
        }
    }
}

void dfs2(int x, int p) {
    for(int i = 0; i <= 20; i++) {
        from_top[x][i] += mx[x][i];
    }
    for(pair<int, int> e: g[x]) {
        if(e.f != p) {
            for(int i = 0; i <= 20; i++) {
                from_top[x][min(e.s, i)] -= mx[e.f][i];
            }
            from_top[e.f].fill(0);
            for(int i = 0; i <= 20; i++) {
                from_top[e.f][min(e.s, i)] += from_top[x][i];
            }
            dfs2(e.f, x);
            ++mx[e.f][e.s];
            for(int i = 0; i <= 20; i++) {
                for(int j = 0; j <= 20; j++) {
                    pairs[e.f] = (pairs[e.f] - mul(min({e.s, i, j}), mul(from_top[x][i], mx[e.f][j])) + mod) % mod;
                }
            }
            --mx[e.f][e.s];
            for(int i = 0; i <= 20; i++) {
                from_top[x][min(e.s, i)] += mx[e.f][i];
            }
        }
    }
}

int main() {
    freopen("blockchain_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        vector<array<int, 3>> edges;
        for(int i = 0, a, b, c; i < n - 1; i++) {
            cin >> a >> b >> c;
            g[a - 1].push_back({b - 1, c});
            g[b - 1].push_back({a - 1, c});
            edges.push_back({-c, a - 1, b - 1});
        }
        DSU kruskal(n);
        sort(edges.begin(), edges.end());
        int tot = 0;
        for(array<int, 3> e: edges) {
            int f1 = kruskal.f(e[1]), f2 = kruskal.f(e[2]);
            tot = (tot + mul(-e[0], mul(kruskal.sz[f1], kruskal.sz[f2]))) % mod;
            kruskal.unite(e[1], e[2]);
        }
        dfs(0, 0);
        from_top[0].fill(0);
        dfs2(0, 0);
        int ans = 1;
        for(int i = 1; i < n; i++) {
            ans = mul(ans, (tot + pairs[i]) % mod);
        }
        cout << "Case #" << _ << ": " << ans << endl;
        for(int i = 0; i < n; i++) {
            g[i].clear();
            pairs[i] = 0;
        }
    }
}