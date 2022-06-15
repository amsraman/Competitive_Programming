#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> g[200000];
bool vis[200000], b[200000];

void dfs(int x) {
    vis[x] = b[x] = true;
    for(int v: g[x]) {
        if(!vis[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    vis[n - 1] = true, dfs(n - 2);
    for(int i = 0; i < n; i++) {
        cout << (b[i] ? 'B' : 'A');
    }
    cout << endl;
}