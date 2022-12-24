#include <bits/stdc++.h>

using namespace std;

int node_count;
vector<int> a, link;
vector<vector<int>> par, mx;

int find(int x) {
    return (x == link[x] ? x : link[x] = find(link[x]));
}

void unite(int x, int y, int wt) {
    x = find(x), y = find(y);
    if(x == y) return;
    link[x] = link[y] = par[x][0] = par[y][0] = ++node_count;
    mx[x][0] = wt - a[x], mx[y][0] = wt - a[y];
    a[node_count] += a[x] + a[y];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    node_count = n - 1;
    a.resize(2 * n - 1, 0), link.resize(2 * n - 1);
    par.resize(2 * n - 1, vector<int>(19, 2 * n - 2)), mx.resize(2 * n - 1, vector<int>(19, 0));
    iota(link.begin(), link.end(), 0);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<array<int, 3>> edges(m);
    for(int i = 0; i < m; i++) {
        cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
        --edges[i][1], --edges[i][2];
    }
    sort(edges.begin(), edges.end());
    for(auto [w, x, y]: edges) {
        unite(x, y, w);
    }
    for(int i = 1; i < 19; i++) {
        for(int j = 0; j < 2 * n - 1; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
            mx[j][i] = max(mx[j][i - 1], mx[par[j][i - 1]][i - 1]);
        }
    }
    for(int i = 0, x, k; i < q; i++) {
        cin >> x >> k; --x;
        for(int j = 18; j >= 0; j--) {
            if(mx[x][j] <= k) {
                x = par[x][j];
            }
        }
        x = (mx[x][0] <= k ? par[x][0] : x);
        cout << k + a[x] << '\n';
    }
}