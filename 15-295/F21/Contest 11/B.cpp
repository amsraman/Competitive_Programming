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

int n, q;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    DSU d(2 * n);
    for(int i = 0; i < q; i++) {
        char tp;
        int a, b;
        cin >> tp >> a >> b;
        --a, --b;
        if(tp == 'R') {
            d.unite(2 * a, 2 * b);
            d.unite(2 * a + 1, 2 * b + 1);
        } else if(tp == 'A') {
            d.unite(2 * a + 1, 2 * b);
            d.unite(2 * a, 2 * b + 1);
        } else {
            if(d.f(2 * a) == d.f(2 * b) || d.f(2 * a + 1) == d.f(2 * b + 1)) {
                cout << "R\n";
            } else if(d.f(2 * a + 1) == d.f(2 * b) || d.f(2 * a) == d.f(2 * b + 1)) {
                cout << "A\n";
            } else {
                cout << "?\n";
            }
        }
    }
}