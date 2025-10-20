#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("wiki_race_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<int> p(n, 0), link(n); iota(link.begin(), link.end(), 0);
        vector<vector<int>> g(n);
        for(int i = 1; i < n; i++) {
            cin >> p[i]; --p[i];
            g[p[i]].push_back(i);
        }
        vector<map<string, int>> strs(n);
        map<string, int> frq;
        for(int i = 0; i < n; i++) {
            int m; cin >> m;
            for(int j = 0; j < m; j++) {
                string s; cin >> s;
                ++strs[i][s]; ++frq[s];
            }
        }
        int ans = 0, num_leaves = 0;
        for(int i = 0; i < n; i++) {
            num_leaves += (int) g[i].empty();
            if(p[i] > 0 && g[p[i]].size() == 1 && g[i].size() == 1) {
                link[i] = p[i];
            }
        }
        auto find = [&](int u) -> int {
            vector<int> touched;
            while(u != link[u]) {
                touched.push_back(u);
                u = link[u];
            }
            for(int v: touched) {
                link[v] = u;
            }
            return u;
        };
        vector<bool> dead(n, false);
        for(int i = 0; i < n; i++) {
            int up = find(i);
            if(up != i) {
                if((int) g[up].size() < (int) g[i].size()) swap(g[up], g[i]);
                if((int) strs[up].size() < (int) strs[i].size()) swap(strs[up], strs[i]);
                for(int v: g[i]) {
                    g[up].push_back(v);
                }
                for(auto [s, ct]: strs[i]) {
                    strs[up][s] += ct;
                }
                g[i].clear();
                strs[i].clear();
                dead[i] = true;
            }
        }
        for(int i = 0; i < n; i++) {
            vector<int> thinned;
            for(int j: g[i]) {
                if(!dead[j]) thinned.push_back(j);
            }
            if(dead[i]) thinned.clear();
            g[i] = thinned;
        }
        vector<int> ord; queue<int> q; q.push(0);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            ord.push_back(u);
            for(int v: g[u]) {
                q.push(v);
            }
        }
        reverse(ord.begin(), ord.end());
        vector<bool> res(n, false);
        for(auto [str, ct]: frq) {
            if(ct < num_leaves) continue;
            bool ok = true;
            for(int u: ord) {
                int avail = strs[u][str], need = g[u].empty();
                for(int v: g[u]) {
                    need += 1 - (int) res[v];
                }
                if(need > 1) ok = false;
                res[u] = avail >= need;
            }
            ok &= res[0];
            ans += (int) ok;
            for(int u: ord) {
                res[u] = false;
            }
        }
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}