#include <bits/stdc++.h>

using namespace std;

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

int n, m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    DSU d(n);
    int cc = n;
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        if(d.f(a) != d.f(b)) {
            d.unite(a, b);
            --cc;
        }
        cout << cc << '\n';
    }
}