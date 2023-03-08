// 41 ms
#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int n;
    vector<int> link, sz;
    DSU(int n): n(n), link(n), sz(n, 1) {
        iota(link.begin(), link.end(), 0);
    }
    int find(int x) {
        return (x == link[x] ? x : link[x] = find(link[x]));
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return;
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    DSU d(n);
    while(q--) {
        int type, u, v; cin >> type >> u >> v;
        if(type == 0) {
            d.unite(u, v);
        } else {
            cout << (d.find(u) == d.find(v)) << '\n';
        }
    }
}