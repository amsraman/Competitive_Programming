#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int r, c, cc;
vector<int> sz(4, 0), id(4, 3);
vector<vector<int>> comp, msk;
vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
vector<string> grid;
vector<vector<bool>> outside;

void dfs(int x, int y) {
    comp[x][y] = cc; ++sz[cc];
    for(pair<int, int> d: dir) {
        if(x + d.f >= 0 && x + d.f < r + 2 && y + d.s >= 0 && y + d.s < c + 2 && comp[x + d.f][y + d.s] == -1 && grid[x + d.f][y + d.s] == '.') {
            dfs(x + d.f, y + d.s);
        }
    }
}

void trace(int x, int y, pair<int, int> d, int cur) {
    int num_adj = ((grid[x - 1][y] != '.') + (grid[x + 1][y] != '.') + (grid[x][y - 1] != '.') + (grid[x][y + 1] != '.'));
    msk[x][y] = (msk[x][y] | cur);
    for(pair<int, int> dd: dir) {
        if(comp[x + dd.f][y + dd.s] == 0) {
            outside[x][y] = true;
        }
    }
    if(num_adj == 2) {
        for(pair<int, int> dd: dir) {
            if((dd.f != -d.f || dd.s != -d.s) && grid[x + dd.f][y + dd.s] != '.' && !(msk[x + dd.f][y + dd.s] & cur)) {
                trace(x + dd.f, y + dd.s, dd, cur);
            }
        }
    } else {
        trace(x + d.f, y + d.s, d, cur);
    }
}

int main() {
    cin >> r >> c;
    grid.resize(r + 2, string(c + 2, '.'));
    comp.resize(r + 2, vector<int>(c + 2, -1)); msk.resize(r + 2, vector<int>(c + 2, 0));
    outside.resize(r + 2, vector<bool>(c + 2, false));
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= c; j++) {
            cin >> grid[i][j];
        }
    }
    for(int i = 0; i < r + 2; i++) {
        for(int j = 0; j < c + 2; j++) {
            if(comp[i][j] == -1 && grid[i][j] == '.') {
                dfs(i, j);
                cc++;
            }
            if(grid[i][j] == 'A') {
                trace(i, j, {-1, -1}, 1);
            }
            if(grid[i][j] == 'B') {
                trace(i, j, {-1, -1}, 2);
            }
        }
    }
    for(int i = 1; i < r + 1; i++) {
        for(int j = 1; j < c + 1; j++) {
            if(comp[i][j] <= 0) continue;
            for(pair<int, int> d: dir) {
                if(msk[i + d.f][j + d.s] == 1 && outside[i + d.f][j + d.s]) {
                    id[comp[i][j]] = 1;
                } else if(msk[i + d.f][j + d.s] == 2 && outside[i + d.f][j + d.s]) {
                    id[comp[i][j]] = 2;
                }
            }
        }
    }
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            if(id[j] == i) {
                cout << sz[j] << " ";
            }
        }
    }
    cout << '\n';
}
