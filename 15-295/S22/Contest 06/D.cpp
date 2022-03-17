#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int INF = 5e7;

int n, m, dist[1000][1000][3], cd[3][3];
pair<int, int> dir[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
string grid[1000];
bool vis[1000][1000][3];

bool ok(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    for(int t = 0; t < 3; t++) {
        queue<pair<int, int>> q;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                dist[i][j][t] = INF;
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == char('1' + t)) {
                    q.push({i, j});
                    dist[i][j][t] = 0;
                    vis[i][j][t] = true;
                }
            }
        }
        for(int i = 0; i < 3; i++) {
            cd[t][i] = INF;
        }
        while(!q.empty()) {
            pair<int, int> tp = q.front();
            q.pop();
            if(grid[tp.f][tp.s] != '.') {
                int cur = grid[tp.f][tp.s] - '1';
                cd[t][cur] = min(cd[t][cur], dist[tp.f][tp.s][t]);
            }
            for(pair<int, int> d: dir) {
                if(ok(tp.f + d.f, tp.s + d.s) && grid[tp.f + d.f][tp.s + d.s] != '#' && !vis[tp.f + d.f][tp.s + d.s][t]) {
                    q.push({tp.f + d.f, tp.s + d.s});
                    dist[tp.f + d.f][tp.s + d.s][t] = dist[tp.f][tp.s][t] + 1;
                    vis[tp.f + d.f][tp.s + d.s][t] = true;
                }
            }
        }
    }
    int ans = INF;
    for(int i = 0; i < 3; i++) {
        ans = min(ans, cd[i][0] + cd[i][1] + cd[i][2] - cd[i][i] - 2);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '.') {
                ans = min(ans, dist[i][j][0] + dist[i][j][1] + dist[i][j][2] - 2);
            }
        }
    }
    cout << (ans > 1e7 ? -1 : ans) << endl;
}