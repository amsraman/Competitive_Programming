#include <bits/stdc++.h>

using namespace std;

int n, m, k, w, dist[1000][1000], ans;
vector<array<int, 3>> edges;
vector<int> mst[1001];
vector<pair<int,int>> moves;
string levels[1000][10];

struct dsu {
    int link[1001], sz[1001];

    void init() {
        for(int i = 0; i <= k; i++) {
            link[i] = i, sz[i] = 1;
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
        link[y] = x, sz[x] += sz[y];
    }
} mst_dsu;

void dfs(int x, int p) {
    for(int i: mst[x]) {
        if(i != p) {
            moves.push_back({i, x});
            dfs(i, x);
        }
    }
}

int main() {
    cin >> n >> m >> k >> w;
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < n; j++) {
            cin >> levels[i][j];
        }
    }
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {
            for(int x = 0; x < n; x++) {
                for(int y = 0; y < m; y++) {
                    dist[i][j] += (levels[i][x][y] != levels[j][x][y]);
                }
            }
        }
    }
    mst_dsu.init();
    for(int i = 0; i < k; i++) {
        edges.push_back({n * m, 0, i + 1});
        for(int j = i + 1; j < k; j++) {
            edges.push_back({w * dist[i][j], i + 1, j + 1});
        }
    }
    sort(edges.begin(), edges.end());
    for(array<int, 3> e: edges) {
        if(mst_dsu.f(e[1]) != mst_dsu.f(e[2])) {
            mst_dsu.unite(e[1], e[2]);
            mst[e[1]].push_back(e[2]);
            mst[e[2]].push_back(e[1]);
            ans += e[0];
        }
    }
    dfs(0, 0);
    cout << ans << endl;
    for(pair<int, int> m: moves) {
        cout << m.first << " " << m.second << endl;
    }
}