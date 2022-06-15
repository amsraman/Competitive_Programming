// 1060 ms
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template<class B>
struct SparseTable : public B {
    using T = typename B::T;

    int n;
    vector<vector<T>> st;

    SparseTable(int n, vector<T> & a): n(n), st(n, vector<T>(__lg(n) + 1, B::e)) {
        for(int i = 0; i < n; i++) {
            st[i][0] = a[i];
        }
        int lev = __lg(n);
        for(int i = 1; i <= lev; i++) {
            for(int j = 0; j < n; j++) {
                st[j][i] = B::comb(st[j][i - 1], st[min(n - 1, j + (1 << (i - 1)))][i - 1]);
            }
        }
    }

    T qry(int l, int r) {
        int lev = __lg(r - l + 1);
        return B::comb(st[l][lev], st[r - (1 << lev) + 1][lev]);
    }
};

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

int t;
vector<int> in, out, dep, ord_time, ord;
vector<vector<int>> g;

struct Info {
    using T = int;
    const T e = INT_MAX;

    T comb(T a, T b) {
        if(a == INT_MAX) {
            return b;
        }
        if(b == INT_MAX) {
            return a;
        }
        return (dep[a] < dep[b] ? a : b);
    }
};

void dfs(int u, int p) {
    ord_time[u] = ord.size(), in[u] = t++;
    ord.push_back(u);
    for(int v: g[u]) {
        if(v != p) {
            dep[v] = dep[u] + 1, dfs(v, u);
            ord.push_back(u);
        }
    }
    out[u] = t;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    g.resize(n), in.resize(n), out.resize(n), dep.resize(n, 0), ord_time.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, 0);
    vector<ll> init(n + 1, 0);
    for(int i = 0; i < n; i++) {
        init[in[i]] += a[i], init[out[i]] -= a[i];
    }
    FenwickTree<ll> ft(n + 1, init);
    SparseTable<Info> lca((int) ord.size(), ord);
    while(q--) {
        int type;
        cin >> type;
        if(type == 0) {
            int p, x;
            cin >> p >> x;
            a[p] += x;
            ft.upd(in[p], x), ft.upd(out[p], -x);
        } else {
            int u, v;
            cin >> u >> v;
            if(ord_time[u] > ord_time[v]) {
                swap(u, v);
            }
            int l = lca.qry(ord_time[u], ord_time[v]);
            cout << ft.qry(in[u]) + ft.qry(in[v]) - 2 * ft.qry(in[l]) + a[l] << '\n';
        }
    }
}