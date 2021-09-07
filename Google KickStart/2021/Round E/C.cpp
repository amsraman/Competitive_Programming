#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, m, h1[1000][1000], h2[1000][1000], v1[1000][1000], v2[1000][1000];
string grid[1000];

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> m;
        for(int i = 0; i < n; i++) {
            cin >> grid[i];
        }
        for(int i = 0; i < n; i++) {
            int pv = -1;
            for(int j = 0; j < m; j++) {
                if(grid[i][j] != '#') {
                    if(pv == -1) {
                        pv = j;
                    }
                    h1[i][j] = pv;
                } else {
                    pv = -1;
                }
            }
            pv = -1;
            for(int j = m - 1; j >= 0; j--) {
                if(grid[i][j] != '#') {
                    if(pv == -1) {
                        pv = j;
                    }
                    h2[i][j] = pv;
                } else {
                    pv = -1;
                }
            }
        }
        for(int i = 0; i < m; i++) {
            int pv = -1;
            for(int j = 0; j < n; j++) {
                if(grid[j][i] != '#') {
                    if(pv == -1) {
                        pv = j;
                    }
                    v1[j][i] = pv;
                } else {
                    pv = -1;
                }
            }
            pv = -1;
            for(int j = n - 1; j >= 0; j--) {
                if(grid[j][i] != '#') {
                    if(pv == -1) {
                        pv = j;
                    }
                    v2[j][i] = pv;
                } else {
                    pv = -1;
                }
            }
        }
        queue<pair<int, int>> q;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] != '.' && grid[i][j] != '#') {
                    q.push({i, j});
                }
            }
        }
        int num_filled = 0;
        while(!q.empty()) {
            int x = q.front().f, y = q.front().s;
            q.pop();
            pair<int, int> op_h = {x, h1[x][y] + h2[x][y] - y};
            pair<int, int> op_v = {v1[x][y] + v2[x][y] - x, y};
            if(grid[op_h.f][op_h.s] == '.') {
                grid[op_h.f][op_h.s] = grid[x][y];
                q.push(op_h);
                ++num_filled;
            }
            if(grid[op_v.f][op_v.s] == '.') {
                grid[op_v.f][op_v.s] = grid[x][y];
                q.push(op_v);
                ++num_filled;
            }
        }
        cout << "Case #" << _ << ": " << num_filled << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
    }
}