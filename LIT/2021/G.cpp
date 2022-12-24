#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

struct Line {
    ll m, b; mutable ll ep;
    bool operator<(const Line & l) const {
        return m < l.m;
    }
    bool operator<(ll x) const {
        return ep < x;
    }
};

struct LineContainer : multiset<Line, less<>> { // defaults to max
    static const ll INF = LLONG_MAX;
    ll div(ll x, ll y) {
        return x / y - ((x ^ y) < 0 && x % y);
    }
    bool upd(iterator x, iterator y) {
        if(y == end()) {
            x->ep = INF;
            return false;
        }
        if(x->m == y->m) x->ep = (x->b < y->b ? -INF : INF);
        else x->ep = div(x->b - y->b, y->m - x->m);
        return x->ep >= y->ep;
    }
    void add(ll m, ll b) {
        auto z = insert({m, b, 0}), y = z++, x = y;
        while(upd(y, z)) z = erase(z);
        if(x != begin() && upd(--x, y)) upd(x, y = erase(y));
        while((y = x) != begin() && (--x)->ep >= y->ep) upd(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto it = *lower_bound(x);
        return it.m * x + it.b;
    }
};

const int lim = 1e9;
const ll INF = 0xfffffffffffffff;

int node_count;
vector<int> link, val;
vector<vector<int>> par;
vector<LineContainer> hull;

int find(int x) {
    return (x == link[x] ? x : link[x] = find(link[x]));
}

void unite(int x, int y) { // kruskal reconstruction tree
    x = find(x), y = find(y);
    if(x == y) return;
    link[x] = link[y] = node_count++;
    par[x][0] = par[y][0] = node_count - 1;
    val[node_count - 1] = max(val[x], val[y]);
    for(auto [m, b, ep]: hull[x]) hull[node_count - 1].add(m, b);
    for(auto [m, b, ep]: hull[y]) hull[node_count - 1].add(m, b);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, q, x, y; cin >> n >> m >> q >> x >> y; --x, --y;
    vector<vector<int>> grid(n, vector<int>(n));
    vector<array<int, 3>> sorted;
    vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vector<ll>> dist(n * n, vector<ll>(m, INF));
    vector<vector<bool>> done(n, vector<bool>(n, false));
    vector<LineContainer> inclusive_hull(n * n);
    link.resize(2 * n * n - 1); val.resize(2 * n * n - 1), hull.resize(2 * n * n - 1);
    par.resize(2 * n * n - 1, vector<int>(18));
    iota(link.begin(), link.end(), 0); iota(par[0].begin(), par[0].end(), 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> grid[i][j];
            sorted.push_back({grid[i][j], i, j});
            val[n * i + j] = grid[i][j];
        }
    }
    dist[n * x + y][0] = grid[x][y];
    for(int i = 0; i < m; i++) {
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < n; y++) {
                if(dist[n * x + y][i] < INF) {
                    hull[n * x + y].add(-i, -dist[n * x + y][i] + grid[x][y]);
                    inclusive_hull[n * x + y].add(-i - 1, -dist[n * x + y][i]);
                }
                if(i == m - 1) continue;
                for(auto [dx, dy]: dirs) {
                    if(x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < n) {
                        dist[n * (x + dx) + y + dy][i + 1] = min(dist[n * (x + dx) + y + dy][i + 1], dist[n * x + y][i] + grid[x + dx][y + dy]);
                    }
                }
            }
        }
    }
    sort(sorted.begin(), sorted.end());
    node_count = n * n;
    for(auto [w, x, y]: sorted) {
        for(auto [dx, dy]: dirs) {
            if(x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < n && done[x + dx][y + dy] && find(n * x + y) != find(n * (x + dx) + y + dy)) {
                unite(n * x + y, n * (x + dx) + y + dy);
            }
        }
        done[x][y] = true;
    }
    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 2 * n * n - 1; j++) {
            par[j][i + 1] = par[par[j][i]][i];
        }
    }
    ll ans = 0;
    for(int i = 0, a, b, s, w; i < q; i++) {
        cin >> a >> b >> s >> w;
        a = (a + ans - 1) % n, b = (b + ans - 1) % n, s = (s + ans - 1) % lim + 1, w = (w + ans - 1) % lim + 1;
        int node = n * a + b;
        if(grid[a][b] > s) {
            cout << (ans = -inclusive_hull[node].query(w)) << '\n';
            continue;
        }
        for(int j = 17; j >= 0; j--) {
            if(val[par[node][j]] <= s) {
                node = par[node][j];
            }
        }
        cout << (ans = -hull[node].query(w)) << '\n';
    }
}