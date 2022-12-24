#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct FenwickTree {
    int n;
    vector<T> bit;
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

vector<int> link, sz, tour1, tour2;
vector<vector<int>> dsu_graph;

int find(int x) {
    return (x == link[x] ? x : link[x] = find(link[x]));
}

void unite(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return;
    if(sz[x] < sz[y]) swap(x, y);
    link[y] = x, sz[x] += sz[y], dsu_graph[x].push_back(y);
}

void dfs(int u) {
    tour1.push_back(u);
    for(int v: dsu_graph[u]) {
        dfs(v);
    }
}

vector<int> check_validity(int n, vector<int> x, vector<int> y, vector<int> s, vector<int> e, vector<int> l, vector<int> r) {
    int m = x.size(), q = s.size();
    link.resize(n);
    vector<int> pos1(n), pos2(n), num(q, 0), ans(q);
    vector<pair<int, int>> were(q), wolf(q);
    vector<vector<int>> g(n), rem(n), pts(n), add(n);
    FenwickTree<int> ft(n);
    for(int i = 0; i < m; i++) {
        g[x[i]].push_back(y[i]);
        g[y[i]].push_back(x[i]);
    }
    auto proc = [&](int start, int end, int step) { // wolf then were
        iota(link.begin(), link.end(), 0), sz.resize(n, 1), dsu_graph.resize(n);
        swap(tour1, tour2), swap(were, wolf);
        vector<vector<int>> handle(n);
        for(int i = 0; i < q; i++) {
            swap(s[i], e[i]), swap(l[i], r[i]);
            handle[l[i]].push_back(i);
        }
        for(int i = start; i != end; i += step) {
            for(int j: g[i]) {
                if(step * j < step * i) {
                    unite(i, j);
                }
            }
            for(int ind: handle[i]) {
                were[ind] = {find(s[ind]), sz[find(s[ind])]};
            }
        }
        dfs(find(0));
        sz.clear(), dsu_graph.clear();
    };
    proc(0, n, 1), proc(n - 1, -1, -1);
    for(int i = 0; i < n; i++) {
        pos1[tour1[i]] = i, pos2[tour2[i]] = i;
    }
    for(int i = 0; i < n; i++) {
        pts[pos1[tour2[i]]].push_back(i);
    }
    for(int i = 0; i < q; i++) {
        were[i] = {pos1[were[i].first], pos1[were[i].first] + were[i].second - 1};
        wolf[i] = {pos2[wolf[i].first], pos2[wolf[i].first] + wolf[i].second - 1};
        rem[were[i].first].push_back(i), add[were[i].second].push_back(i);
    }
    for(int i = 0; i < n; i++) {
        for(int ind: rem[i]) {
            num[ind] -= ft.qry(wolf[ind].first, wolf[ind].second);
        }
        for(int p: pts[i]) {
            ft.upd(p, 1);
        }
        for(int ind: add[i]) {
            num[ind] += ft.qry(wolf[ind].first, wolf[ind].second);
        }
    }
    for(int i = 0; i < q; i++) {
        ans[i] = num[i] > 0;
    }
    return ans;
}

int main() {
    vector<int> ans = check_validity(6, {5, 1, 1, 3, 3, 5}, {1, 2, 3, 4, 0, 2}, {4, 4, 5}, {2, 2, 4}, {1, 2, 3}, {2, 2, 4});
    for(int a: ans) {
        cout << a << " ";
    }
    cout << endl;
}