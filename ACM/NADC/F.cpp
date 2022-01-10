#include <bits/stdc++.h>

using namespace std;

int n, k, num;
vector<int> g[500];
vector<bool> vis;

void dfs(int x) {
    vis[x] = true, ++num;
    for(int u: g[x]) {
        if(!vis[u]) {
            dfs(u);
        }
    }
}

int main() {
    cin >> n >> k;
    vis.resize(n);
    for(int i = 0, sz; i < n; i++) {
        cin >> sz;
        for(int j = 0, v; j < sz; j++) {
            cin >> v;
            g[v - 1].push_back(i);
        }
    }
    for(int i = 0; i < n; i++) {
        fill(vis.begin(), vis.end(), false);
        num = 0;
        dfs(i);
        cout << (num > k) << endl;
    }
}