#include <bits/stdc++.h>

using namespace std;

using fl = long double;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<deque<int>> grp(n);
    vector<int> par(n), lst(n, 0), id(n), lp(n); vector<fl> tm(n), p(n);
    priority_queue<tuple<fl, int, int>, vector<tuple<fl, int, int>>, greater<tuple<fl, int, int>>> q;
    vector<bool> dead(n, false);
    for(int i = 0; i < n; i++) {
        cin >> tm[i] >> p[i] >> par[i]; --par[i];
        p[i] = 1 - p[i];
        grp[i].push_back(i);
        q.push({tm[i] / p[i], i, 0});
        id[i] = lp[i] = i;
    }
    while(!q.empty()) {
        auto [_, u, ts] = q.top(); q.pop();
        if(ts != lst[u]) continue;
        int pr = par[u];
        if(pr == -1) continue;
        pr = id[pr], u = id[u];
        if(tm[pr] * p[u] >= tm[u] * p[pr]) {
            int sz1 = (int) grp[pr].size(), sz2 = grp[u].size(), up = lp[pr];
            dead[lp[u]] = true;
            if(sz1 >= sz2) {
                tm[pr] = tm[pr] + tm[u] * (1 - p[pr]);
                p[pr] = p[pr] + p[u] - p[pr] * p[u];
                for(int v: grp[u]) {
                    grp[pr].push_back(v);
                    id[v] = pr;
                }
                grp[u].clear();
            } else {
                tm[u] = tm[pr] + tm[u] * (1 - p[pr]);
                p[u] = p[pr] + p[u] - p[pr] * p[u];
                reverse(grp[pr].begin(), grp[pr].end());
                for(int v: grp[pr]) {
                    grp[u].push_front(v);
                    id[v] = u;
                }
                lp[u] = up;
                grp[pr].clear();
            }
            q.push({tm[id[up]] / p[id[up]], up, ++lst[up]});
        }
    }
    vector<pair<fl, int>> alive;
    for(int i = 0; i < n; i++) {
        if(!dead[i]) {
            alive.emplace_back(tm[id[i]] / p[id[i]], i);
        }
    }
    sort(alive.begin(), alive.end());
    for(auto [_, i]: alive) {
        for(int val: grp[id[i]]) {
            cout << val + 1 << '\n';
        }
    }
}