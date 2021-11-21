#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, k, sx, sy, fx, fy, dist[1000][1000];
string grid[1000];

int main() {
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    cin >> sx >> sy >> fx >> fy;
    --sx, --sy, --fx, --fy;
    queue<pair<int, int>> q;
    q.push({sx, sy});
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            dist[i][j] = INF;
        }
    }
    dist[sx][sy] = 0;
    while(!q.empty()) {
        int x = q.front().f, y = q.front().s;
        q.pop();
        for(int i = 1; i <= k; i++) {
            if(x + i >= n || grid[x + i][y] == '#' || (dist[x + i][y] < dist[x][y] + 1)) {
                break;
            }
            if(dist[x + i][y] == INF) {
                q.push({x + i, y});
                dist[x + i][y] = dist[x][y] + 1;
            }
        }
        for(int i = 1; i <= k; i++) {
            if(x - i < 0 || grid[x - i][y] == '#' || (dist[x - i][y] < dist[x][y] + 1)) {
                break;
            }
            if(dist[x - i][y] == INF) {
                q.push({x - i, y});
                dist[x - i][y] = dist[x][y] + 1;
            }
        }
        for(int i = 1; i <= k; i++) {
            if(y + i >= m || grid[x][y + i] == '#' || (dist[x][y + i] < dist[x][y] + 1)) {
                break;
            }
            if(dist[x][y + i] == INF) {
                q.push({x, y + i});
                dist[x][y + i] = dist[x][y] + 1;
            }
        }
        for(int i = 1; i <= k; i++) {
            if(y - i < 0 || grid[x][y - i] == '#' || (dist[x][y - i] < dist[x][y] + 1)) {
                break;
            }
            if(dist[x][y - i] == INF) {
                q.push({x, y - i});
                dist[x][y - i] = dist[x][y] + 1;
            }
        }
    }
    cout << (dist[fx][fy] == INF ? -1 : dist[fx][fy]) << endl;
}