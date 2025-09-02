#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> e(n);
        for(int i = 0, k; i < n; i++) {
            cin >> k; e[i].resize(k);
            for(int j = 0; j < k; j++) {
                cin >> e[i][j];
            }
        }
        vector<vector<pair<int, int>>> st(n), en(n);
        for(int i = 0, l, r; i < m; i++) {
            cin >> l >> r; --l, --r;
            st[l].emplace_back(l, r); en[r].emplace_back(l, r);
        }
        bool res = true;
        vector<int> cur; multiset<pair<int, int>> ins;
        for(int i = 0; i < n; i++) {
            for(auto [l, r]: st[i]) {
                ins.emplace(-r, l);
            }
            int num_ins = (int) ins.size();
            for(int val: e[i]) {
                cur.push_back(min(num_ins, val));
            }
            sort(cur.begin(), cur.end());
            for(int j = 0; j < (int) cur.size(); j++) {
                if(j + 1 > cur[j]) res = false;
            }
            if(res) {
                for(int j = 0; j < (int) cur.size(); j++) {
                    ins.erase(ins.begin());
                }
            }
            cur.clear();
            for(auto [l, r]: en[i]) {
                if(ins.count({-r, l})) {
                    ins.erase(ins.find(make_pair(-r, l)));
                }
            }
        }
        cout << (res ? "YES" : "NO") << '\n';
    }
}
/*
Lot of parts to this problem.
*/