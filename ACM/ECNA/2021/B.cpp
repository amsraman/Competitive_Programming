#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, pages[1000], in_deg[1000], out_deg[1000], par[1000], tot[1000][1000], ans = INF;
vector<int> g[1000];
bool anc[1000][1000];

void dfs(int x, int y) {
    for(int u: g[x]) {
        dfs(u, y);
        anc[y][u] = true;
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> pages[i];
    }
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        ++out_deg[u - 1], ++in_deg[v - 1];
        g[u - 1].push_back(v - 1);
        par[v - 1] = u - 1;
    }
    for(int i = 0; i < n; i++) {
        dfs(i, i);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) {
                tot[i][j] = pages[i];
                if(in_deg[i] > 0) {
                    tot[i][j] += tot[par[i]][par[j]];
                }
            } else {
                if(in_deg[i] > 0) {
                    tot[i][j] = tot[par[i]][j];
                    if(!anc[i][j]) {
                        tot[i][j] += pages[i];
                    }
                } else if(in_deg[j] > 0) {
                    tot[i][j] = tot[i][par[j]];
                    if(!anc[j][i]) {
                        tot[i][j] += pages[j];
                    }
                } else {
                    tot[i][j] = pages[i] + pages[j];
                }
            }
            if(out_deg[i] == 0 && out_deg[j] == 0 && i != j) {
                ans = min(ans, tot[i][j]);
            }
        }
    }
    cout << ans << endl;
}