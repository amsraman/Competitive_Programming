#include <bits/stdc++.h>
typedef long long ll;

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

int c, n, q, t, in[100000], out[100000], dep[100000];
vector<int> g[100000];

void dfs(int x, int p) {
    in[x] = t++;
    for(int u: g[x]) {
        if(u != p) {
            dep[u] = dep[x] + 1;
            dfs(u, x);
        }
    }
    out[x] = t - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> c;
    while(c--) {
        cin >> n >> q;
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        t = 0;
        dfs(0, 0);
        FenwickTree<ll> ft(n);
        for(int i = 0, a, b, x; i < q; i++) {
            cin >> a >> b >> x;
            if(x == 0) {
                if(dep[a - 1] < dep[b - 1]) {
                    swap(a, b);
                }
                cout << abs(ft.range_qry(in[a - 1], out[a - 1])) << '\n';
            } else {
                ft.upd(in[a - 1], x);
                ft.upd(in[b - 1], -x);
            }
        }
        for(int i = 0; i < n; i++) {
            g[i].clear();
        }
    }
}