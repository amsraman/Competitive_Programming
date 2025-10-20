#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("monkey_around_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<int> p(n);
        for(int i = 0; i < n; i++) {
            cin >> p[i]; --p[i];
        }
        vector<pair<int, int>> pieces, res;
        for(int i = 0; i < n;) {
            if(p[i] == 0) {
                int ep = i;
                while(ep < n - 1 && p[ep + 1] == p[ep] + 1) {
                    ++ep;
                }
                pieces.emplace_back(ep - i + 1, 0); i = ep + 1;
            } else {
                int ep = i;
                while(p[ep] != p[i] - 1) {
                    ++ep;
                }
                pieces.emplace_back(ep - i + 1, p[i]); i = ep + 1;
            }
        }
        int sz = (int) pieces.size(), num_moves = 0;
        for(int i = sz - 1; i >= 0; i--) {
            auto [len, rot] = pieces[i];
            int cur_rotation = (rot - num_moves % len);
            if(cur_rotation < 0) cur_rotation += len;
            num_moves += cur_rotation;
            for(int j = 0; j < cur_rotation; j++) {
                res.emplace_back(2, -1);
            }
            res.emplace_back(1, len);
        }
        reverse(res.begin(), res.end());
        assert((int) res.size() <= 2 * n);
        cout << "Case #" << _ << ": " << (int) res.size() << '\n';
        for(auto [tp, val]: res) {
            if(tp == 1) {
                cout << tp << " " << val << '\n';
            } else {
                cout << tp << '\n';
            }
        }
    }
}