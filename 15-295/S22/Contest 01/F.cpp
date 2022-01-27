// I blame this string of wrong answers on Walter White's incompetence
#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m;
vector<pair<int, int>> g[100000][2];
vector<int> ans[2], col[2], vc[2];
bool bad[2];

void dfs(int x, int c) {
    vc[col[c][x]].push_back(x);
    for(pair<int, int> p: g[x][c]) {
        if(col[c][p.f] == -1) {
            col[c][p.f] = (col[c][x] ^ p.s);
            dfs(p.f, c);
        } else if(col[c][p.f] != (col[c][x] ^ p.s)) {
            bad[c] = true;
        }
    }
}

void att(int c) {
    col[c].resize(n, -1);
    for(int i = 0; i < n; i++) {
        if(col[c][i] == -1) {
            col[c][i] = 0;
            dfs(i, c);
        }
        if(bad[c]) {
            ans[c].clear();
            vc[0].clear(), vc[1].clear();
            return;
        }
        if(vc[0].size() < vc[1].size()) {
            for(int i: vc[0]) {
                ans[c].push_back(i + 1);
            }
        } else {
            for(int i: vc[1]) {
                ans[c].push_back(i + 1);
            }
        }
        vc[0].clear(), vc[1].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0, u, v; i < m; i++) {
        char tp;
        cin >> u >> v >> tp;
        --u, --v;
        if(tp == 'R') {
            g[u][0].push_back({v, 0});
            g[v][0].push_back({u, 0});
            g[u][1].push_back({v, 1});
            g[v][1].push_back({u, 1});
        } else {
            g[u][0].push_back({v, 1});
            g[v][0].push_back({u, 1});
            g[u][1].push_back({v, 0});
            g[v][1].push_back({u, 0});
        }
    }
    att(0), att(1);
    if(bad[0] && bad[1]) {
        cout << "-1";
    } else if(!bad[0] && (bad[1] || ans[0].size() < ans[1].size())) {
        cout << ans[0].size() << '\n';
        for(int i: ans[0]) {
            cout << i << " ";
        }
    } else {
        cout << ans[1].size() << '\n';
        for(int i: ans[1]) {
            cout << i << " ";
        }
    }
    cout << '\n';
}