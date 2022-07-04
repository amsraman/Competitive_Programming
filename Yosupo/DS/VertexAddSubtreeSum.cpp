// 333 ms
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template<typename T>
struct FenwickTree {
    size_t n;
    vector<T> bit;

    FenwickTree(size_t n): n(n), bit(n, 0) {};

    FenwickTree(int n, vector<T> & init): n(n), bit(n) {
        copy(init.begin(), init.end(), bit.begin());
        for(int i = 1; i <= n; i++) {
            if(i + (i & -i) <= n) {
                bit[i + (i & -i) - 1] += bit[i - 1];
            }
        }
    }

    T qry(int k) {
        T ret = 0;
        for(k++; k > 0; k -= (k & -k)) {
            ret += bit[k - 1];
        }
        return ret;
    }

    T range_qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }

    void upd(int k, T x) {
        for(k++; k <= n; k += (k & -k)) {
            bit[k - 1] += x;
        }
    }
};

int t;
vector<int> in, out;
vector<vector<int>> g;

void dfs(int u) {
    in[u] = t++;
    for(int v: g[u]) {
        dfs(v);
    }
    out[u] = t - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    FenwickTree<ll> ft(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    in.resize(n), out.resize(n), g.resize(n);
    for(int i = 0, p; i < n - 1; i++) {
        cin >> p;
        g[p].push_back(i + 1);
    }
    dfs(0);
    for(int i = 0; i < n; i++) {
        ft.upd(in[i], a[i]);
    }
    for(int i = 0, tp, u, x; i < q; i++) {
        cin >> tp >> u;
        if(tp == 0) {
            cin >> x;
            ft.upd(in[u], x);
        } else {
            cout << ft.range_qry(in[u], out[u]) << '\n';
        }
    }
}