#include <bits/stdc++.h>

using namespace std;

int n, init[100000], goal[100000], p[100000], gp[100000];
vector<int> g[100000], ans;

void dfs(int x, int pr) {
    for(int u: g[x]) {
        if(u != pr) {
            p[u] = x;
            dfs(u, x);
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
    for(int i = 0; i < n; i++) {
        cin >> init[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> goal[i];
    }
    gp[0] = p[0] = -1;
    dfs(0, 0);
    for(int i = 1; i < n; i++) {
        gp[i] = p[p[i]];
    }
    for(int i = 0; i < n; i++) {
        if(gp[i] == -1) {
            if(init[i] ^ goal[i]) {
                ans.push_back(i + 1);
            }
        } else {
            if(init[i] ^ goal[i] ^ init[gp[i]] ^ goal[gp[i]]) {
                ans.push_back(i + 1);
            }
        }
    }
    cout << ans.size() << '\n';
    for(int a: ans) {
        cout << a << '\n';
    }
}