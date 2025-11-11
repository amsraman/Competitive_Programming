#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int n; vector<int> link, sz;
    DSU(int n): n(n), link(n), sz(n, 1) {
        iota(link.begin(), link.end(), 0);
    }
    int find(int x) {
        return (x == link[x] ? x : link[x] = find(link[x]));
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return;
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x;
    }
};

const int mx = 1e5;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    vector<vector<pair<int, int>>> at_elev(mx);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j]; --grid[i][j];
            at_elev[grid[i][j]].emplace_back(i, j);
        }
    }
    vector<vector<bool>> attr(n, vector<bool>(m, false));
    int a; cin >> a;
    for(int i = 0, r, c; i < a; i++) {
        cin >> r >> c; --r, --c;
        attr[r][c] = true;
    }
    vector<vector<pair<int, int>>> qrs(mx);
    int q; cin >> q;
    for(int i = 0, c, v; i < q; i++) {
        cin >> c >> v; --c;
        qrs[c].emplace_back(v, i);
    }
    vector<pair<int, int>> res(q, make_pair(-1, -1));
    auto conv = [&](int x, int y) {
        return m * x + y;
    };
    vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    auto ok = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };
    vector<int> num_attr(n * m, 0), mn_at_comp(n * m);
    vector<set<int>> mn_at_attr(11); DSU d(n * m);
    iota(mn_at_comp.begin(), mn_at_comp.end(), 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            num_attr[conv(i, j)] = (int) attr[i][j];
        }
    }
    for(int i = 0; i < mx; i++) {
        for(auto [x, y]: at_elev[i]) {
            if(d.sz[d.find(conv(x, y))] == 1) {
                mn_at_attr[num_attr[conv(x, y)]].insert(conv(x, y));
            }
            for(auto [dx, dy]: dirs) {
                if(ok(x + dx, y + dy) && grid[x + dx][y + dy] <= grid[x][y] && grid[x + dx][y + dy] >= grid[x][y] - 1 && d.find(conv(x, y)) != d.find(conv(x + dx, y + dy))) {
                    int g1 = d.find(conv(x, y)), g2 = d.find(conv(x + dx, y + dy));
                    mn_at_attr[num_attr[g1]].erase(mn_at_comp[g1]);
                    mn_at_attr[num_attr[g2]].erase(mn_at_comp[g2]);
                    int new_num = num_attr[g1] + num_attr[g2], new_mn = min(mn_at_comp[g1], mn_at_comp[g2]);
                    d.unite(g1, g2);
                    num_attr[d.find(conv(x, y))] = new_num, mn_at_comp[d.find(conv(x, y))] = new_mn;
                    mn_at_attr[num_attr[d.find(conv(x, y))]].insert(mn_at_comp[d.find(conv(x, y))]);
                }
            }
        }
        for(auto [v, ind]: qrs[i]) {
            int use = 1e9;
            for(int num = v; num <= 10; num++) {
                if(!mn_at_attr[num].empty()) {
                    use = min(use, *mn_at_attr[num].begin());
                }
            }
            if(use < 1e9) {
                res[ind] = make_pair(use / m + 1, use % m + 1);
            }
        }
    }
    for(auto [x, y]: res) {
        cout << x << " " << y << '\n';
    }
}