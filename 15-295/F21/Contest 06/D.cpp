#include <bits/stdc++.h>

using namespace std;

int n, m, dist[3000][3000], s1, s2, t1, t2, l1, l2, ans = 5000;
vector<int> g[3000];
bool vis[3000][3000];

void bfs(int x) {
    for(int i = 0; i < n; i++) {
        dist[x][i] = 5000;
    }
    dist[x][x] = 0, vis[x][x] = true;
    queue<int> q;
    q.push(x);
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        for(int i: g[cur]) {
            if(!vis[x][i]) {
                dist[x][i] = dist[x][cur] + 1;
                q.push(i);
                vis[x][i] = vis[x][cur];
            }
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
    cin >> s1 >> s2 >> l1 >> t1 >> t2 >> l2;
    --s1, --s2, --t1, --t2;
    for(int i = 0; i < n; i++) {
        bfs(i);
    }
    if(dist[s1][s2] <= l1 && dist[t1][t2] <= l2) {
        ans = dist[s1][s2] + dist[t1][t2];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(dist[s1][i] + dist[i][j] + dist[j][s2] <= l1 && dist[t1][i] + dist[i][j] + dist[j][t2] <= l2) {
                ans = min(ans, dist[s1][i] + dist[t1][i] + dist[i][j] + dist[j][s2] + dist[j][t2]);
            }
            if(dist[s1][i] + dist[i][j] + dist[j][s2] <= l1 && dist[t2][i] + dist[i][j] + dist[j][t1] <= l2) {
                ans = min(ans, dist[s1][i] + dist[t2][i] + dist[i][j] + dist[j][s2] + dist[j][t1]);
            }
            if(dist[s2][i] + dist[i][j] + dist[j][s1] <= l1 && dist[t1][i] + dist[i][j] + dist[j][t2] <= l2) {
                ans = min(ans, dist[s2][i] + dist[t1][i] + dist[i][j] + dist[j][s1] + dist[j][t2]);
            }
            if(dist[s2][i] + dist[i][j] + dist[j][s1] <= l1 && dist[t2][i] + dist[i][j] + dist[j][t1] <= l2) {
                ans = min(ans, dist[s2][i] + dist[t2][i] + dist[i][j] + dist[j][s1] + dist[j][t1]);
            }
        }
    }
    cout << (ans == 5000 ? -1 : m - ans) << endl;
}