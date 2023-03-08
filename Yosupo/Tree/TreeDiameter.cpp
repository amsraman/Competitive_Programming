// 611 ms
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> st;
    vector<vector<pair<int, int>>> g(n);
    for(int i = 0, a, b, c; i < n - 1; i++) {
        cin >> a >> b >> c;
        g[a].push_back({b, c}); g[b].push_back({a, c});
    }
    int p1, p2; ll ans = 0;
    auto dfs = [&](auto rec, int u, int p) -> pair<ll, int> {
        pair<ll, int> mx1 = {0, u}, mx2 = {0, u};
        for(auto [v, w]: g[u]) {
            if(v != p) {
                pair<ll, int> res = rec(rec, v, u); res.first += w;
                if(res > mx1) mx2 = mx1, mx1 = res;
                else mx2 = max(mx2, res);
            }
        }
        if(mx1.first + mx2.first > ans) {
            ans = mx1.first + mx2.first;
            p1 = mx1.second, p2 = mx2.second;
        }
        return mx1;
    };
    auto get_path = [&](auto rec, int u, int p, int dest) -> void {
        st.push_back(u);
        if(u == dest) {
            cout << st.size() << '\n';
            for(int s: st) cout << s << " ";
            cout << '\n';
        }
        for(auto [v, w]: g[u]) {
            if(v != p) {
                rec(rec, v, u, dest);
            }
        }
        st.pop_back();
    };
    dfs(dfs, 0, 0);
    cout << ans << " ";
    get_path(get_path, p1, p1, p2);
}