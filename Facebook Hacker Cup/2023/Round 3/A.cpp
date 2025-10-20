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
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        sz[x] += sz[y], link[y] = x;
    }
};

int main() {
    ifstream cin("spooky_splits_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m; cin >> n >> m;
        DSU d(n);
        for(int i = 0, u, v; i < m; i++) {
            cin >> u >> v; --u, --v;
            if(d.find(u) != d.find(v)) {
                d.unite(u, v);
            }
        }
        vector<int> bins;
        for(int i = 0; i < n; i++) {
            if(i == d.find(i)) bins.push_back(d.sz[i]);
        }
        set<vector<int>> vis; int k;
        sort(bins.begin(), bins.end());
        reverse(bins.begin(), bins.end());
        auto gen = [&](auto rec, vector<int> st, int lev) -> bool {
            if(vis.count(st)) return false;
            if(lev == (int) bins.size()) return true;
            int sz = (int) st.size();
            set<int> seen;
            for(int i = 0; i < sz; i++) {
                if(seen.count(st[i])) continue;
                if(st[i] + bins[lev] <= k) {
                    st[i] += bins[lev];
                    if(rec(rec, st, lev + 1)) return true;
                    st[i] -= bins[lev];
                }
                seen.insert(st[i]);
            }
            if(sz < n / k && bins[lev] <= k) {
                st.push_back(bins[lev]);
                if(rec(rec, st, lev + 1)) return true;
                st.pop_back();
            }
            vis.insert(st);
            return false;
        };
        vector<bool> pos(n + 1, false);
        for(k = 1; k <= n; k++) {
            if(n % k != 0 || pos[k]) continue;
            vector<int> init;
            if(gen(gen, init, 0)) {
                for(int i = k; i <= n; i += k) {
                    if(n % i == 0) pos[i] = true;
                }
            }
            vis.clear();
        }
        cout << "Case #" << _ << ": ";
        for(int i = n; i >= 1; i--) {
            if(pos[i]) cout << n / i << " ";
        }
        cout << '\n';
    }
}