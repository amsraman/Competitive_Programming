#include <bits/stdc++.h>

using namespace std;

int n, q;
vector<vector<int>> g, dp;

void dfs(int u) {
    dp[u][1] = 1;
    for(int v: g[u]) {
        dfs(v);
        dp[u][0] += (v >= n ? dp[v][0] : max(dp[v][0], dp[v][1]));
        dp[u][1] += (v >= n ? dp[v][1] - 1 : dp[v][0]);
    }
}

int main() {
    cin >> n >> q;
    g.resize(n + q), dp.resize(n + q, vector<int>(2, 0));
    vector<array<int, 3>> circles(n + q), ev;
    vector<int> par(n + q, -1);
    for(int i = 0; i < n; i++) {
        cin >> circles[i][0] >> circles[i][1] >> circles[i][2];
        ev.push_back({circles[i][0] - circles[i][2], 1, i});
        ev.push_back({circles[i][0] + circles[i][2], -1, i});
    }
    for(int i = n; i < n + q; i++) {
        cin >> circles[i][0] >> circles[i][1] >> circles[i][2];
        ev.push_back({circles[i][0] - circles[i][2], 1, i});
        ev.push_back({circles[i][0] + circles[i][2], -1, i});
    }
    sort(ev.begin(), ev.end());
    auto cmp = [&](pair<int, int> c1, pair<int, int> c2) -> bool {
        if(c1.first == c2.first) {
            return (c1.second == -1 && c2.second == 1);
        }
        bool sw = false, ans;
        if(circles[c1.first][0] - circles[c1.first][2] > circles[c2.first][0] - circles[c2.first][2]) {
            swap(c1, c2), sw = true;
        }
        auto [x1, y1, rad1] = circles[c1.first];
        auto [x2, y2, rad2] = circles[c2.first];
        int dx = x2 - x1 - rad2, dy = y2 - y1;
        if(c1.second == 1) {
            ans = (dy >= 0 && 1LL * (rad1 - dx) * (rad1 + dx) <= 1LL * dy * dy);
        } else {
            ans = (dy >= 0 || 1LL * (rad1 - dx) * (rad1 + dx) >= 1LL * dy * dy);
        }
        return ans ^ sw;
    };
    set<pair<int, int>, decltype(cmp)> circle_set(cmp);
    for(auto [x, type, ind]: ev) {
        if(type == 1) {
            auto it = circle_set.upper_bound({ind, 1});
            if(it != circle_set.end()) {
                if(it->second == 1) {
                    g[it->first].push_back(ind);
                    par[ind] = it->first;
                } else if(par[it->first] != -1) {
                    g[par[it->first]].push_back(ind);
                    par[ind] = par[it->first];
                }
            }
            circle_set.insert({ind, 1}); circle_set.insert({ind, -1});
        } else {
            circle_set.erase({ind, 1}); circle_set.erase({ind, -1});
        }
    }
    for(int i = 0; i < n + q; i++) {
        if(par[i] == -1) {
            dfs(i);
        }
    }
    for(int i = 0; i < q; i++) {
        cout << max(dp[i + n][0], dp[i + n][1]) << '\n';
    }
}