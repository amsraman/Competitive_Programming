#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ifstream cin("plan_out_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m; cin >> n >> m;
        vector<vector<pair<int, int>>> g(n);
        vector<int> deg(n, 0); vector<pair<int, int>> edges;
        for(int i = 0, a, b; i < m; i++) {
            cin >> a >> b; --a, --b;
            g[a].emplace_back(b, i); g[b].emplace_back(a, i);
            ++deg[a], ++deg[b];
            edges.emplace_back(a, b);
        }
        vector<int> odds; int edge_ct = m;
        for(int i = 0; i < n; i++) {
            if(deg[i] % 2 == 1) {
                odds.push_back(i);
            }
        }
        for(int i = 0; i < (int) odds.size(); i += 2) {
            g[odds[i]].emplace_back(odds[i + 1], edge_ct);
            g[odds[i + 1]].emplace_back(odds[i], edge_ct);
            ++edge_ct;
        }
        vector<bool> used(edge_ct, false), vis(n, false);
        vector<int> ptr(n, 0);
        auto euler_cycle = [&](vector<vector<pair<int, int>>> & g, int root) {
            vector<int> ans;
            stack<int> st, disp; st.push(root);
            while(!st.empty()) {
                int u = st.top(); vis[u] = true;
                if((int) disp.size() == (int) st.size()) {
                    ans.push_back(disp.top()); disp.pop();
                }
                while(ptr[u] < (int) g[u].size() && used[g[u][ptr[u]].second]) ++ptr[u];
                if(ptr[u] < (int) g[u].size()) {
                    used[g[u][ptr[u]].second] = true;
                    disp.push(g[u][ptr[u]].second);
                    st.push(g[u][ptr[u]].first);
                } else {
                    st.pop();
                }
            }
            return ans;
        };
        vector<int> col(m, -1), res(n, 0);
        for(int i = 0; i < n; i++) {
            if(vis[i]) continue;
            auto cur_cyc = euler_cycle(g, i);
            if(cur_cyc.empty()) continue;
            int sz = (int) cur_cyc.size(), pt = 0;
            while(pt < sz && cur_cyc[pt] < m) ++pt;
            if(pt == m) pt = 0;
            for(int i = 0; i < sz; i++) {
                int ind = (i + pt) % sz;
                if(cur_cyc[ind] < m) {
                    col[cur_cyc[ind]] = i % 2 + 1;
                }
            }
        }
        ll tot = 0;
        for(int i = 0; i < m; i++) {
            auto [u, v] = edges[i];
            if(col[i] == 1) {
                ++res[u], ++res[v];
            } else {
                --res[u], --res[v];
            }
        }
        for(int i = 0; i < n; i++) {
            int one = (deg[i] + res[i]) / 2, two = (deg[i] - res[i]) / 2;
            tot += 1LL * one * one + 1LL * two * two;
        }
        cout << "Case #" << _ << ": " << tot << " ";
        for(int i = 0; i < m; i++) {
            cout << col[i];
        }
        cout << '\n';
    }
}