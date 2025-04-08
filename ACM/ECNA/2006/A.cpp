#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    for(int _ = 1; n > 0; _++) {
        int e; cin >> e;
        vector<vector<int>> g(n);
        for(int i = 0, x, y; i < e; i++) {
            cin >> x >> y;
            g[x - 1].push_back(y - 1); g[y - 1].push_back(x - 1);
        }
        bool res = false;
        if(e == n - 1) {
            int ct = 0;
            vector<int> par(n, -1);
            auto dfs1 = [&](auto rec, int u) -> void {
                ++ct;
                for(int v: g[u]) {
                    if(par[v] == -1) {
                        par[v] = u;
                        rec(rec, v);
                    }
                }
            };
            par[0] = 0;
            dfs1(dfs1, 0);
            if(ct == n) { // connected
                for(int i = 0; i < n; i++) {
                    fill(par.begin(), par.end(), -1);
                    par[i] = i;
                    dfs1(dfs1, i);
                    vector<bool> in(n, false);
                    for(int j = i + 1; j < n; j++) {
                        fill(in.begin(), in.end(), false);
                        for(int cur = j; ; cur = par[cur]) {
                            in[cur] = true;
                            if(cur == i) {
                                break;
                            }
                        }
                        bool ok = true;
                        for(int i = 0; i < n; i++) {
                            if(!in[i] && g[i].size() != 1) {
                                ok = false;
                            }
                        }
                        if(ok) {
                            res = true;
                        }
                    }
                }
            }
        }
        cout << "Graph " << _ << " is ";
        if(!res) {
            cout << "not ";
        }
        cout << "a caterpillar.\n";
        cin >> n;
    }
}