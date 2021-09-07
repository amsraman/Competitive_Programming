#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, k;
vector<vector<int>> grid, ps, diff;
vector<vector<bool>> vis;

int get_ps(int lx, int ux, int ly, int uy) {
    return ps[ux + 1][uy + 1] - ps[ux + 1][ly] - ps[lx][uy + 1] + ps[lx][ly];
}

bool ok(int sz) {
    queue<pair<int, int>> q;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            diff[i][j] = vis[i][j] = 0;
        }
    }
    pair<int, int> starting_pos = {-1, -1};
    for(int i = sz - 1; i < n; i++) {
        for(int j = sz - 1; j < m; j++) {
            if(get_ps(i - sz + 1, i, j - sz + 1, j) == 0) {
                starting_pos = {i, j};
            }
        }
    }
    if(starting_pos.f == -1) {
        return false;
    }
    q.push(starting_pos);
    vis[starting_pos.f][starting_pos.s] = true;
    while(!q.empty()) {
        int x = q.front().f, y = q.front().s;
        ++diff[x - sz + 1][y - sz + 1], --diff[x + 1][y - sz + 1], --diff[x - sz + 1][y + 1], ++diff[x + 1][y + 1];
        q.pop();
        if(x >= sz && get_ps(x - sz, x - sz, y - sz + 1, y) == 0 && !vis[x - 1][y]) {
            q.push({x - 1, y});
            vis[x - 1][y] = true;
        }
        if(y >= sz && get_ps(x - sz + 1, x, y - sz, y - sz) == 0 && !vis[x][y - 1]) {
            q.push({x, y - 1});
            vis[x][y - 1] = true;
        }
        if(x < n - 1 && get_ps(x + 1, x + 1, y - sz + 1, y) == 0 && !vis[x + 1][y]) {
            q.push({x + 1, y});
            vis[x + 1][y] = true;
        }
        if(y < m - 1 && get_ps(x - sz + 1, x, y + 1, y + 1) == 0 && !vis[x][y + 1]) {
            q.push({x, y + 1});
            vis[x][y + 1] = true;
        }
    }
    int num_visited = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i) {
                diff[i][j] += diff[i - 1][j];
            }
            if(j) {
                diff[i][j] += diff[i][j - 1];
            }
            if(i && j) {
                diff[i][j] -= diff[i - 1][j - 1];
            }
            num_visited += (diff[i][j] > 0 || grid[i][j] == 1);
        }
    }
    return num_visited == n * m;
}

int main() {
    cin >> n >> m >> k;
    grid.resize(n, vector<int>(m, 0));
    ps.resize(n + 1, vector<int>(m + 1));
    diff.resize(n + 1, vector<int>(m + 1));
    vis.resize(n, vector<bool>(m));
    for(int i = 0, x, y; i < k; i++) {
        cin >> x >> y;
        grid[x - 1][y - 1] = 1;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ps[i + 1][j + 1] = ps[i + 1][j] + ps[i][j + 1] - ps[i][j] + grid[i][j];
        }
    }
    int lb = 1, ub = n;
    while(lb < ub) {
        int mid = (lb + ub + 1) / 2;
        if(ok(mid)) {
            lb = mid;
        } else {
            ub = mid - 1;
        }
    }
    cout << (ok(1) ? ub : -1) << endl;
}