#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> go(n);
    for(int i = 0, a; i < m; i++) {
        cin >> a; --a;
        go[a].push_back({i, a + 1});
        go[a + 1].push_back({i, a});
    }
    vector<int> ans(n);
    for(int i = 0; i < n; i++) {
        int cur = i, tm = 0;
        while(true) {
            auto it = lower_bound(go[cur].begin(), go[cur].end(), make_pair(tm, 0));
            if(it == go[cur].end()) break;
            tm = it->first + 1, cur = it->second;
        }
        ans[cur] = i + 1;
    }
    for(int a: ans) {
        cout << a << '\n';
    }
}