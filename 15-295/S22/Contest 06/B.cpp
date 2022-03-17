#include <bits/stdc++.h>

using namespace std;

const int INF = 500;

int n, m, dist[400][2];
vector<int> g[400][2];
bool in[400][400], vis[400][2];

int main() {
    cin >> n >> m;
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[u - 1][0].push_back(v - 1);
        g[v - 1][0].push_back(u - 1);
        in[u - 1][v - 1] = in[v - 1][u - 1] = true;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(!in[i][j]) {
                g[i][1].push_back(j);
            }
        }
    }
    for(int t = 0; t < 2; t++) {
        for(int i = 1; i < n; i++) {
            dist[i][t] = INF;
        }
        queue<int> q;
        q.push(0);
        vis[0][t] = true;
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            for(int u: g[v][t]) {
                if(!vis[u][t]) {
                    dist[u][t] = dist[v][t] + 1;
                    q.push(u);
                    vis[u][t] = true;
                }
            }
        }
    }
    int ans = max(dist[n - 1][0], dist[n - 1][1]);
    cout << (ans == INF ? -1 : ans) << endl;
}