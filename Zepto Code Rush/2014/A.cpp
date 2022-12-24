#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, x; cin >> n >> x;
    vector<vector<pair<int, int>>> types(2);
    for(int i = 0, type, h, m; i < n; i++) {
        cin >> type >> h >> m;
        types[type].push_back({h, m});
    }
    sort(types[0].begin(), types[0].end()); sort(types[1].begin(), types[1].end());
    int ans = 0;
    for(int it = 0; it < 2; it++) {
        vector<int> ptr(2, 0);
        vector<multiset<int>> sts(2);
        int tp = it, jump = x, cur = 0;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < types[i].size(); j++) {
                if(types[i][j].first <= x) {
                    sts[i].insert(types[i][j].second); ++ptr[i];
                }
            }
        }
        while(!sts[tp].empty()) {
            int best = *(--sts[tp].end());
            sts[tp].erase(--sts[tp].end()); jump += best; cur++;
            tp ^= 1;
            while(ptr[tp] < types[tp].size() && types[tp][ptr[tp]].first <= jump) {
                sts[tp].insert(types[tp][ptr[tp]++].second);
            }
        }
        ans = max(ans, cur);
    }
    cout << ans << endl;
}