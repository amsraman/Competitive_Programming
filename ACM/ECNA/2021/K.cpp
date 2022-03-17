#include <bits/stdc++.h>

using namespace std;

const int INF = 1e5;

int h, w, pieces[100][100], dist[9902][3], ans;
vector<int> g[9902][3];
set<int> sts[3];
set<pair<int, int>> edges;
bool vis[9902][3];

void add_edge(int x, int y) {
    if(edges.count({x, y}) || x == y) {
        return;
    }
    g[x][0].push_back(y);
    g[y][1].push_back(x);
    g[y][2].push_back(x);
    edges.insert({x, y});
}

void bfs(int x) {
    for(int i = 0; i < 9902; i++) {
        dist[i][x] = INF;
    }
    queue<int> q;
    for(int i: sts[x]) {
        q.push(i);
        dist[i][x] = 0;
        vis[i][x] = true;
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v: g[u][x]) {
            if(!vis[v][x]) {
                q.push(v);
                dist[v][x] = dist[u][x] + 1;
                vis[v][x] = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> h >> w;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            cin >> pieces[i][j];
            if(i == 0) {
                sts[1].insert(pieces[i][j] - 1);
            }
            if(i == h - 1) {
                sts[0].insert(pieces[i][j] - 1);
            }
        }
    }
    if(sts[1].size() > 1) {
        int f = *sts[1].begin();
        sts[1].erase(f);
        sts[2].insert(f);
    }
    for(int i = h - 1; i > 0; i--) {
        for(int j = 0; j < w; j++) {
            add_edge(pieces[i][j] - 1, pieces[i - 1][j] - 1);
        }
    }
    for(int i = 0; i < 3; i++) {
        bfs(i);
        if(i > 0 && !sts[i].empty()) {
            ans += dist[*sts[i].begin()][0] + 1;
        }
    }
    for(int i = 0; i < 9902; i++) {
        int cur = dist[i][0] + 1;
        for(int j = 1; j < 3; j++) {
            if(!sts[j].empty()) {
                cur += dist[i][j];
            }
        }
        ans = min(ans, cur);
    }
    cout << ans << '\n';
}