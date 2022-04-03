#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

template<typename T>
struct FenwickTree {
    size_t n;
    vector<T> bit;

    FenwickTree(size_t n): n(n), bit(n, 0) {};

    T qry(int k) {
        T ret = 0;
        for(k++; k > 0; k -= (k & (-k))) {
            ret += bit[k - 1];
        }
        return ret;
    }

    T range_qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }

    void upd(int k, T x) {
        for(k++; k <= n; k += (k & (-k))) {
            bit[k - 1] += x;
        }
    }
};

int n, q, t, in[300000], out[300000];
ld cur[300000], mx = log(1e9);
vector<int> g[300000];

void dfs(int x, int p) {
    in[x] = t++;
    for(int u: g[x]) {
        if(u != p) {
            dfs(u, x);
        }
    }
    out[x] = t - 1;
}

int main() {
    cin >> n;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs(0, 0);
    FenwickTree<ld> ft(n + 1);
    cin >> q;
    cout << fixed << setprecision(9);
    for(int i = 0, t, x, y; i < q; i++) {
        cin >> t >> x >> y;
        if(t == 1) {
            ft.upd(in[x - 1], log((ld) y) - cur[x - 1]);
            cur[x - 1] = log((ld) y);
        } else {
            ld res = ft.range_qry(in[x - 1], out[x - 1]) - ft.range_qry(in[y - 1], out[y - 1]);
            cout << exp(min(res, mx)) << '\n';
        }
    }
}