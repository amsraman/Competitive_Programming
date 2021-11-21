#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int t, n, q, p[200000], prob[200000], dep[200000], par[200000][20];
pair<int, int> eq[200000][20];
vector<array<int, 3>> g[200000];

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

void dfs(int x) {
    for(array<int, 3> e: g[x]) {
        prob[e[0]] = (mul(prob[x], e[1]) + mul((1 - prob[x] + mod) % mod, e[2])) % mod;
        par[e[0]][0] = x;
        dep[e[0]] = dep[x] + 1;
        eq[e[0]][0] = {(e[1] - e[2] + mod) % mod, e[2]};
        dfs(e[0]);
    }
}

pair<int, int> compose(pair<int, int> eq1, pair<int, int> eq2) {
    // a * (cx + d) + b
    return {mul(eq1.first, eq2.first), (mul(eq1.first, eq2.second) + eq1.second) % mod};
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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    int den = exp(1e6, mod - 2);
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> q >> prob[0];
        prob[0] = mul(prob[0], den);
        for(int i = 0; i < n - 1; i++) {
            int trans1, trans2;
            cin >> p[i] >> trans1 >> trans2;
            trans1 = mul(trans1, den), trans2 = mul(trans2, den);
            g[p[i] - 1].push_back({i + 1, trans1, trans2});
        }
        dfs(0), eq[0][0] = {1, 0};
        for(int i = 1; i < 20; i++) {
            for(int j = 0; j < n; j++) {
                par[j][i] = par[par[j][i - 1]][i - 1];
                eq[j][i] = compose(eq[j][i - 1], eq[par[j][i - 1]][i - 1]);
            }
        }
        cout << "Case #" << _ << ": ";
        for(int i = 0, u, v; i < q; i++) {
            cin >> u >> v;
            --u, --v;
            int l = lca(u, v), pos = prob[l], neg = (1 - prob[l] + mod) % mod;
            int cur_u = u, cur_v = v;
            pair<int, int> trns1 = {1, 0}, trns2 = {1, 0};
            for(int j = 19; j >= 0; j--) {
                if((dep[cur_u] - dep[l]) >> j) {
                    trns1 = compose(trns1, eq[cur_u][j]);
                    cur_u = par[cur_u][j];
                }
                if((dep[cur_v] - dep[l]) >> j) {
                    trns2 = compose(trns2, eq[cur_v][j]);
                    cur_v = par[cur_v][j];
                }
            }
            pos = mul(pos, mul((trns1.first + trns1.second) % mod, (trns2.first + trns2.second) % mod));
            neg = mul(neg, mul(trns1.second, trns2.second));
            cout << (pos + neg) % mod << " ";
        }
        cout << '\n';
        for(int i = 0; i < n; i++) {
            g[i].clear();
        }
    }
}