#include <bits/stdc++.h>

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

int main() {
    int n, m; cin >> n >> m;
    vector<pair<int, int>> edge, sorted_edge;
    set<pair<int, int>> tree;
    for(int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        edge.emplace_back(u - 1, v - 1);
        sorted_edge.emplace_back(w, i);
    }
    sort(sorted_edge.begin(), sorted_edge.end());
    DSU mst(n);
    vector<int> add; set<int> rem;
    for(int i = 0; i < n - 1; i++) {
        rem.insert(i), tree.insert(edge[i]);
    }
    for(auto [w, i]: sorted_edge) {
        auto [u, v] = edge[i];
        if(mst.find(u) != mst.find(v)) {
            if(i >= n - 1) add.push_back(i);
            else rem.erase(i);
            mst.unite(u, v);
        }
    }
    vector<pair<int, int>> ans;
    for(int i: rem) {
        tree.erase(edge[i]);
        DSU d(n);
        for(auto [u, v]: tree) {
            d.unite(u, v);
        }
        int take;
        for(int j: add) {
            auto [u, v] = edge[j];
            if(d.find(u) != d.find(v)) {
                take = j;
                break;
            }
        }
        tree.insert(edge[take]);
        ans.emplace_back(i + 1, take + 1);
    }
    cout << ans.size() << '\n';
    for(auto [u, v]: ans) {
        cout << u << " " << v << '\n';
    }
}