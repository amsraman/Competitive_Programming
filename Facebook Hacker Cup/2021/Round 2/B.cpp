#include <bits/stdc++.h>

using namespace std;

int t, n, f[800000], ps[800000], par[800000][21], dep[800000];
vector<int> g[800000], frq[800000], ord;

int lca(int u, int v) {
    if(dep[u] < dep[v]) {
        swap(u, v);
    }
    for(int i = 0; i < 21; i++) {
        if((dep[u] - dep[v]) >> i & 1) {
            u = par[u][i];
        }
    }
    for(int i = 20; i >= 0; i--) {
        if(par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return (u == v ? u : par[u][0]);
}

int main() {
    freopen("chainblock_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        for(int i = 0; i < n; i++) {
            cin >> f[i];
            frq[f[i] - 1].push_back(i);
            ps[i] = 0;
        }
        memset(par, -1, sizeof(par));
        queue<int> q;
        q.push(0), par[0][0] = 0;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            ord.push_back(u);
            for(int v: g[u]) {
                if(par[v][0] == -1) {
                    par[v][0] = u, dep[v] = dep[u] + 1;
                    q.push(v);
                }
            }
        }
        for(int i = 1; i < 21; i++) {
            for(int j = 0; j < n; j++) {
                par[j][i] = par[par[j][i - 1]][i - 1];
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < (int) frq[i].size() - 1; j++) {
                ++ps[frq[i][j]], ++ps[frq[i][j + 1]];
                ps[lca(frq[i][j], frq[i][j + 1])] -= 2;
            }
        }
        reverse(ord.begin(), ord.end());
        for(int u: ord) {
            for(int v: g[u]) {
                if(v != par[u][0]) {
                    ps[u] += ps[v];
                }
            }
        }
        int ans = 0;
        for(int i = 1; i < n; i++) {
            ans += (ps[i] == 0);
        }
        cout << "Case #" << _ << ": " << ans << endl;
        for(int i = 0; i < n; i++) {
            g[i].clear();
            frq[i].clear();
        }
        ord.clear();
    }
}