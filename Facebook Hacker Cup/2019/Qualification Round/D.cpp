#include <bits/stdc++.h>

using namespace std;

int t, n, m, x[120], y[120], z[120], ans[60];
bool pos;

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
        if(x == y) {
            return;
        }
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x;
    }
};

int dfs(int sz, vector<bool> & in) {
    // Try to find a root
    vector<bool> ok(n, true);
    for(int i = 0; i < m; i++) {
        if(in[x[i]] && in[y[i]] && in[z[i]]) {
            ok[x[i]] = (ok[x[i]] & (x[i] == z[i]));
            ok[y[i]] = (ok[y[i]] & (y[i] == z[i]));
        }
    }
    vector<int> possible_roots;
    for(int i = 0; i < n; i++) {
        if(in[i] && ok[i]) {
            possible_roots.push_back(i);
        }
    }
    if(sz == 1) {
        return possible_roots[0];
    }
    if(possible_roots.empty()) {
        pos = false;
        return 1;
    }
    for(int root: possible_roots) {
        DSU d(n);
        in[root] = false;
        for(int i = 0; i < m; i++) {
            if(in[x[i]] && in[y[i]] && in[z[i]]) {
                d.unite(x[i], y[i]);
                d.unite(y[i], z[i]);
            }
        }
        bool root_works = true;
        for(int i = 0; i < m; i++) {
            if(root == z[i] && x[i] != z[i] && y[i] != z[i] && d.f(x[i]) == d.f(y[i])) {
                root_works = false;
            }
        }
        in[root] = true;
        if(!root_works) {
            continue;
        }
        vector<int> part[n];
        for(int i = 0; i < n; i++) {
            if(in[i] && i != root) {
                part[d.f(i)].push_back(i);
            }
        }
        fill(in.begin(), in.end(), false);
        for(int i = 0; i < n; i++) {
            if(!part[i].empty()) {
                for(int v: part[i]) {
                    in[v] = true;
                }
                ans[dfs(part[i].size(), in)] = root + 1;
                for(int v: part[i]) {
                    in[v] = false;
                }
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j: part[i]) {
                in[j] = true;
            }
        }
        in[root] = true;
        return root;
    }
    pos = false;
    return 1;
}

int main() {
    freopen("trees_as_a_service_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> m;
        for(int i = 0; i < m; i++) {
            cin >> x[i] >> y[i] >> z[i];
            --x[i], --y[i], --z[i];
        }
        pos = true;
        memset(ans, 0, sizeof(ans));
        vector<bool> in(n, true);
        dfs(n, in);
        cout << "Case #" << _ << ": ";
        if(pos) {
            for(int i = 0; i < n; i++) {
                cout << ans[i] << " ";
            }
            cout << endl;
        } else {
            cout << "Impossible" << endl;
        }
    }
}
