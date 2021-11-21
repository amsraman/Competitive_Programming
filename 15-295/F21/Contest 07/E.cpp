#include <bits/stdc++.h>

using namespace std;

int n, m, q, ps[501][501][4], st[500][500][9][9];
string grid[500];

int get_ps(int lx, int ly, int ux, int uy, int col) {
    lx = min(max(lx, 0), n - 1);
    ly = min(max(ly, 0), m - 1);
    ux = min(max(ux, 0), n - 1);
    uy = min(max(uy, 0), m - 1);
    return ps[ux + 1][uy + 1][col] - ps[ux + 1][ly][col] - ps[lx][uy + 1][col] + ps[lx][ly][col];
}

bool valid(int x, int y, int sz) {
    int r_square = get_ps(x - sz + 1, y - sz + 1, x, y, 0);
    int g_square = get_ps(x - sz + 1, y + 1, x, y + sz, 1);
    int y_square = get_ps(x + 1, y - sz + 1, x + sz, y, 2);
    int b_square = get_ps(x + 1, y + 1, x + sz, y + sz, 3);
    return min({r_square, g_square, y_square, b_square}) == sz * sz;
}

int qry(int lx, int ly, int ux, int uy) {
    if(ux < lx || uy < ly) {
        return 0;
    }
    int d1 = __lg(ux - lx + 1);
    int d2 = __lg(uy - ly + 1);
    ux -= (1 << d1) - 1;
    uy -= (1 << d2) - 1;
    return max({st[lx][ly][d1][d2], st[ux][ly][d1][d2], st[lx][uy][d1][d2], st[ux][uy][d1][d2]});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> q;
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 'R') {
                ++ps[i + 1][j + 1][0];
            } else if(grid[i][j] == 'G') {
                ++ps[i + 1][j + 1][1];
            } else if(grid[i][j] == 'Y') {
                ++ps[i + 1][j + 1][2];
            } else {
                ++ps[i + 1][j + 1][3];
            }
        }
    }
    for(int t = 0; t < 4; t++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                ps[i][j][t] += ps[i - 1][j][t] + ps[i][j - 1][t] - ps[i - 1][j - 1][t];
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int cur = 0;
            while(valid(i, j, cur + 1)) {
                ++cur;
            }
            st[i][j][0][0] = cur;
        }
    }
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            for(int k = 0; k < n; k++) {
                for(int l = 0; l < m; l++) {
                    if(i > 0) {
                        st[k][l][i][j] = max(st[k][l][i - 1][j], st[min(n - 1, k + (1 << (i - 1)))][l][i - 1][j]);
                    } else if(j > 0) {
                        st[k][l][i][j] = max(st[k][l][i][j - 1], st[k][min(m - 1, l + (1 << (j - 1)))][i][j - 1]);
                    }
                }
            }
        }
    }
    for(int i = 0, r1, c1, r2, c2; i < q; i++) {
        cin >> r1 >> c1 >> r2 >> c2;
        --r1, --c1, --r2, --c2;
        int lb = 0, ub = min(c2 - c1 + 1, r2 - r1 + 1);
        while(lb < ub) {
            int mid = (lb + ub + 1) / 2;
            if(qry(r1 + mid - 1, c1 + mid - 1, r2 - mid, c2 - mid) >= mid) {
                lb = mid;
            } else {
                ub = mid - 1;
            }
        }
        cout << 4 * ub * ub << '\n';
    }
}