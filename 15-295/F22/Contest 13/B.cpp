#include <bits/stdc++.h>

using namespace std;

int ans;
vector<int> dep;
vector<vector<int>> g;
vector<bool> vis;

void dfs(int u) {
    vis[u] = true; ans = max(ans, dep[u]);
    for(int v: g[u]) {
        dep[v] = dep[u] + 1; dfs(v);
    }
}

int main() {
    int n; cin >> n;
    vector<int> p(n); g.resize(n); vis.resize(n, false); dep.resize(n, 1);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        if(p[i] != -1) {
            g[p[i] - 1].push_back(i);
        }
    }
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    cout << ans << endl;
}