#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

struct DSU {
    int n;
    vector<int> link, sz;
 
    DSU(int n): n(n), link(n), sz(n) {
        for(int i = 0; i < n; i++) {
            link[i] = i;
            sz[i] = 1;
        }
    }
 
    int f(int x) {
        return (x == link[x] ? x : link[x] = f(link[x]));
    }
 
    void unite(int x, int y) {
        x = f(x), y = f(y);
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x;
    }
};

int r, c;
string dc = "SWNE";
pair<int, int> dir[4] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
vector<vector<char>> eg;
vector<vector<bool>> spanning_tree;
string ans;

bool ok(int x, int y, int d) {
    pair<int, int> dr = dir[d];
    if(x + dr.f < 0 || x + dr.f >= 2 * r || y + dr.s < 0 || y + dr.s >= 2 * c) {
        return false;
    }
    int conv = c * (x >> 1) + (y >> 1);
    pair<int, int> nxt = {x + dr.f, y + dr.s};
    if(eg[nxt.f][nxt.s] == '#') {
        return false;
    }
    if(((x >> 1) != (nxt.f >> 1) || (y >> 1) != (nxt.s >> 1)) && !spanning_tree[conv][d]) {
        return false;
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> r >> c;
        vector<string> grid(r);
        eg.resize(2 * r, vector<char>(2 * c));
        int open = 0;
        for(int i = 0; i < r; i++) {
            cin >> grid[i];
            for(int j = 0; j < c; j++) {
                open += grid[i][j] == '*';
                eg[2 * i][2 * j] = eg[2 * i + 1][2 * j] = eg[2 * i][2 * j + 1] = eg[2 * i + 1][2 * j + 1] = grid[i][j];
            }
        }
        DSU ds(r * c);
        auto conv = [](int x, int y) {
            return c * x + y;
        };
        int ec = 0;
        spanning_tree.resize(r * c, vector<bool>(4, false));
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(i < r - 1 && grid[i][j] == '*' && grid[i + 1][j] == '*' && ds.f(conv(i, j)) != ds.f(conv(i + 1, j))) {
                    spanning_tree[conv(i, j)][0] = spanning_tree[conv(i + 1, j)][2] = true;
                    ds.unite(conv(i, j), conv(i + 1, j));
                    ++ec;
                }
                if(j < c - 1 && grid[i][j] == '*' && grid[i][j + 1] == '*' && ds.f(conv(i, j)) != ds.f(conv(i, j + 1))) {
                    spanning_tree[conv(i, j)][3] = spanning_tree[conv(i, j + 1)][1] = true;
                    ds.unite(conv(i, j), conv(i, j + 1));
                    ++ec;
                }
            }
        }
        ans = "S";
        int x = 1, y = 0, d = 0;
        while(true) {
            if(x + y == 0) {
                break;
            }
            if(!ok(x, y, d)) {
                d = (d + 3) % 4;
                ans += dc[d];
                x += dir[d].f, y += dir[d].s;
            } else {
                ans += dc[d];
                pair<int, int> nxt = {x + dir[d].f, y + dir[d].s};
                if(ok(nxt.f, nxt.s, (d + 1) % 4)) {
                    d = (d + 1) % 4;
                }
                x = nxt.f, y = nxt.s;
            }
        }
        cout << "Case #" << _ << ": ";
        if(ans.length() == 4 * open) {
            cout << ans << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
        eg.clear(), spanning_tree.clear();
    }
}