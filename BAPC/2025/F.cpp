#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

struct DSU {
    int n; vector<int> link, sz;
    DSU(int n): n(n), link(n), sz(n, 1) {
        iota(link.begin(), link.end(), 0);
    }
    int find(int x) {
        return (x == link[x] ? x : link[x] = find(link[x]));
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x;
    }
};

template <typename T>
struct FenwickTree {
    int n; vector<T> bit;
    FenwickTree(int n): n(n), bit(n, 0) {};
    FenwickTree(vector<T> & init): n((int) init.size()), bit((int) init.size()) {
        copy(init.begin(), init.end(), bit.begin());
        for(int i = 1; i <= n; i++) {
            if(i + (i & -i) <= n) {
                bit[i + (i & -i) - 1] += bit[i - 1];
            }
        }
    }
    T qry(int k) {
        T ret = 0;
        for(k++; k > 0; k -= k & -k) {
            ret += bit[k - 1];
        }
        return ret;
    }
    T qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }
    void upd(int k, T x) {
        for(k++; k <= n; k += k & -k) {
            bit[k - 1] += x;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<vector<int>> g(n); vector<int> par(n, -1);
        for(int i = 1; i < n; i++) {
            cin >> par[i]; --par[i];
            g[par[i]].push_back(i);
        }
        FenwickTree<ll> ft(n + 1); DSU d(n);
        vector<int> in(n), out(n), rt(n); int tm = 0;
        vector<ll> val(n, 0);
        iota(rt.begin(), rt.end(), 0);
        auto dfs = [&](auto rec, int u) -> ll {
            in[u] = tm++; val[u] = a[u];
            for(int v: g[u]) {
                ll dwn = rec(rec, v);
                val[u] += max(dwn, 0LL);
            }
            out[u] = tm;
            ft.upd(in[u], max(0LL, -val[u]));
            ft.upd(out[u], -max(0LL, -val[u]));
            return val[u];
        };
        dfs(dfs, 0);
        for(int u = 0; u < n; u++) {
            val[u] = max(0LL, -val[u]);
        }
        for(int u = 0; u < n; u++) {
            for(int v: g[u]) {
                if(val[u] == 0 && val[v] == 0) {
                    int up = rt[d.find(u)];
                    d.unite(u, v);
                    rt[d.find(u)] = up;
                }
            }
        }
        int q; cin >> q;
        while(q--) {
            int tp; cin >> tp;
            if(tp == 1) {
                int v, x; cin >> v >> x; --v;
                while(true) {
                    int up = val[v] == 0 ? par[rt[d.find(v)]] : v;
                    if(up == -1) break;
                    if(val[up] <= x) {
                        ft.upd(in[up], -val[up]); ft.upd(out[up], val[up]);
                        x -= val[up]; val[up] = 0;
                        for(int dwn: g[up]) { // unite with children
                            if(val[dwn] != 0) continue;
                            d.unite(up, dwn);
                            rt[d.find(up)] = up;
                        }
                        if(up != 0 && val[par[up]] == 0) {
                            int new_rt = rt[d.find(par[up])];
                            d.unite(up, par[up]);
                            rt[d.find(up)] = new_rt;
                        }
                        continue;
                    }
                    val[up] -= x; ft.upd(in[up], -x); ft.upd(out[up], x);
                    break;
                }
            } else {
                int v; cin >> v; --v;
                cout << max(1LL, ft.qry(in[v])) << '\n';
            }
        }
    }
}