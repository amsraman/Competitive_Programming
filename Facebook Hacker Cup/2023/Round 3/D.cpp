#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ifstream cin("double_stars_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<vector<int>> g(n);
        for(int i = 1, p; i < n; i++) {
            cin >> p; --p;
            g[p].push_back(i); g[i].push_back(p);
        }
        vector<int> topo, par(n, -1), dwn(n, 0);
        queue<int> q; q.push(0);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for(int v: g[u]) {
                if(v != par[u]) {
                    q.push(v); par[v] = u;
                }
            }
        }
        reverse(topo.begin(), topo.end());
        ll ans = 0;
        vector<vector<pair<int, int>>> chn(n);
        for(int u: topo) {
            if(par[u] != -1) dwn[par[u]] = max(dwn[par[u]], dwn[u] + 1);
            for(int v: g[u]) {
                if(v == par[u]) continue;
                chn[u].emplace_back(dwn[v] + 1, v);
            }
        }
        queue<pair<int, int>> q2; q2.push({0, 0});
        while(!q2.empty()) {
            auto [u, tp] = q2.front(); q2.pop();
            if(par[u] != -1) chn[u].emplace_back(tp, par[u]);
            int m1 = 0, m2 = 0;
            for(int v: g[u]) {
                if(v == par[u]) continue;
                m2 = max(m2, dwn[v] + 1);
                if(m1 < m2) swap(m1, m2);
            }
            for(int v: g[u]) {
                if(v == par[u]) continue;
                int other = (dwn[v] + 1 == m1 ? m2 : m1);
                q2.push({v, max(other, tp) + 1});
            }
        }
        for(int i = 0; i < n; i++) {
            sort(chn[i].begin(), chn[i].end());
            reverse(chn[i].begin(), chn[i].end());
        }
        for(int v = 1; v < n; v++) {
            int u = par[v];
            vector<int> l1, l2;
            int sz = min(chn[u].size(), chn[v].size()) - 1;
            for(auto [len, vert]: chn[u]) {
                if(l1.size() == sz) break;
                if(vert != v) l1.push_back(len);
            }
            for(auto [len, vert]: chn[v]) {
                if(l2.size() == sz) break;
                if(vert != u) l2.push_back(len);
            }
            for(int i = 0; i < sz; i++) {
                ans += min(l1[i], l2[i]);
            }
        }
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}