#include <bits/stdc++.h>

using namespace std;

int n, m, col[200000];
vector<int> g[200000], clv[2];
bool vis[200000], bp = true;

void dfs(int x, int c) {
    vis[x] = true;
    col[x] = c;
    clv[col[x] - 1].push_back(x);
    for(int i: g[x]) {
        if(!vis[i]) {
            dfs(i, 3 - c);
        } else if(col[i] == c) {
            bp = false;
        }
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            dfs(i, 1);
        }
    }
    if(!bp) {
        cout << -1 << endl;
    } else {
        cout << clv[0].size() << endl;
        for(int i: clv[0]) {
            cout << i + 1 << " ";
        }
        cout << endl;
        cout << clv[1].size() << endl;
        for(int i: clv[1]) {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
}