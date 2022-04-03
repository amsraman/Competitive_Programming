#include <bits/stdc++.h>

using namespace std;

int n, dm, mx1[300000], mx2[300000], ans[300000];
vector<int> g[300000];

void dfs1(int x, int p) {
    mx1[x] = mx2[x] = 0;
    for(int u: g[x]) {
        if(u != p) {
            dfs1(u, x);
            if(mx1[u] + 1 > mx1[x]) {
                mx2[x] = mx1[x], mx1[x] = mx1[u] + 1;
            } else if(mx1[u] + 1 > mx2[x]) {
                mx2[x] = mx1[u] + 1;
            }
        }
    }
    dm = max(dm, mx1[x] + mx2[x]);
}

void dfs2(int x, int p, int d) {
    ans[x] = max(dm, max(d, mx1[x]) + 1);
    for(int u: g[x]) {
        if(u != p) {
            dfs2(u, x, max(d, (mx1[u] + 1 == mx1[x] ? mx2[x] : mx1[x])) + 1);
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
    dfs1(0, 0), dfs2(0, 0, 0);
    for(int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }
}