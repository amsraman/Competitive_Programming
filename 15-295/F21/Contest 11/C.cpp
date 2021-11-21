#include <bits/stdc++.h>
typedef long long ll;

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

int n, m, k, kid[300000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    vector<array<int, 4>> edges;
    for(int i = 0, a, b, c; i < m; i++) {
        cin >> a >> b >> c;
        edges.push_back({c, a - 1, b - 1, i});
    }
    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());
    vector<DSU> d;
    for(int i = 0; i < k; i++) {
        DSU asdf(n);
        d.push_back(n);
    }
    for(int i = 0; i < m; i++) {
        int lb = 0, ub = k - 1, u = edges[i][1], v = edges[i][2];
        while(lb < ub) {
            int mid = (lb + ub) / 2;
            if(d[mid].f(u) != d[mid].f(v)) {
                ub = mid;
            } else {
                lb = mid + 1;
            }
        }
        if(d[ub].f(u) == d[ub].f(v)) {
            continue;
        }
        d[ub].unite(u, v);
        kid[edges[i][3]] = ub + 1;
    }
    for(int i = 0; i < m; i++) {
        cout << kid[i] << '\n';
    }
}