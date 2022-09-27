#include <bits/stdc++.h>

using namespace std;

int n, q, d[100000];
vector<int> g[100000];

void dfs(int x, int p, int dep) {
    ++d[dep];
    for(int u: g[x]) {
        if(u != p) {
            dfs(u, x, dep + 1);
        }
    }
}

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> q;
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        set<int> go; go.insert(1);
        dfs(0, 0, 0);
        for(int i = 1; i < n; i++) {
            d[i] += d[i - 1]; go.insert(d[i]);
        }
        for(int i = 0, l; i < q; i++) {
            cin >> l;
        }
        cout << "Case #" << _ << ": " << *(--go.upper_bound(q)) << endl;
        for(int i = 0; i < n; i++) {
            g[i].clear(); d[i] = 0;
        }
    }
}