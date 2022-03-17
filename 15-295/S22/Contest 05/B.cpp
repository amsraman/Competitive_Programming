#include <bits/stdc++.h>

using namespace std;

int n, cat[2];
vector<int> g[100000];

void dfs(int x, int p, int d) {
    ++cat[d];
    for(int u: g[x]) {
        if(u != p) {
            dfs(u, x, d ^ 1);
        }
    }
}

int main() {
    cin >> n;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs(0, 0, 0);
    cout << 1LL * cat[0] * cat[1] - n + 1 << '\n';
}