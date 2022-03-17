#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, ans;
pair<int, int> dir[8] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
string grid[100];
bool vis[100][100];

bool ok(int x, int y, int dx, int dy) {
    return (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m);
}

void dfs(int x, int y) {
    vis[x][y] = true;
    for(pair<int, int> d: dir) {
        if(ok(x, y, d.f, d.s) && grid[x + d.f][y + d.s] == '#' && !vis[x + d.f][y + d.s]) {
            dfs(x + d.f, y + d.s);
        }
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '#' && !vis[i][j]) {
                dfs(i, j);
                ++ans;
            }
        }
    }
    cout << ans << endl;
}