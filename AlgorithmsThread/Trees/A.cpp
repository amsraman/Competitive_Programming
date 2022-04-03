#include <bits/stdc++.h>

using namespace std;

int n, mx[300000], ans;
vector<int> g[300000];

void dfs(int x, int p) {
    int mx1 = 0, mx2 = 0;
    for(int u: g[x]) {
        if(u != p) {
            dfs(u, x);
            if(mx[u] + 1 > mx1) {
                mx2 = mx1, mx1 = mx[u] + 1;
            } else if(mx[u] + 1 > mx2) {
                mx2 = mx[u] + 1;
            }
        }
    }
    ans = max(ans, mx1 + mx2);
    mx[x] = mx1;
}

int main() {
    cin >> n;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs(0, 0);
    cout << 3 * ans << endl;
}