#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("warm_up_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<int> a(n), b(n);
        map<int, int> at_val;
        for(int i = 0; i < n; i++) {
            cin >> a[i]; at_val[a[i]] = i;
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
        }
        vector<pair<int, int>> ord;
        for(int i = 0; i < n; i++) {
            ord.emplace_back(a[i], i);
        }
        sort(ord.begin(), ord.end());
        bool bad = false; vector<pair<int, int>> res;
        for(int i = 0; i < n; i++) {
            int ind = ord[i].second;
            if(a[ind] == b[ind]) continue;
            if(a[ind] > b[ind] || !at_val.count(b[ind])) {
                bad = true;
                break;
            }
            res.emplace_back(ind + 1, at_val[b[ind]] + 1);
        }
        cout << "Case #" << _ << ": ";
        if(bad) {
            cout << "-1\n";
        } else {
            cout << (int) res.size() << '\n';
            for(auto [x, y]: res) {
                cout << x << " " << y << '\n';
            }
        }
    }
}