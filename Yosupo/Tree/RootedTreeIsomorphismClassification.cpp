// 523 ms
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, ct = 0; cin >> n;
    vector<vector<int>> g(n);
    for(int i = 1, p; i < n; i++) {
        cin >> p;
        g[i].push_back(p); g[p].push_back(i);
    }
    map<vector<int>, int> id; vector<int> ans(n);
    auto dfs = [&](auto rec, int u, int p) -> int {
        vector<int> ch;
        for(int v: g[u]) {
            if(v != p) {
                ch.push_back(rec(rec, v, u));
            }
        }
        sort(ch.begin(), ch.end());
        if(!id.count(ch)) id[ch] = ct++;
        return ans[u] = id[ch];
    };
    dfs(dfs, 0, 0);
    cout << ct << '\n';
    for(int a: ans) {
        cout << a << " ";
    }
    cout << '\n';
}