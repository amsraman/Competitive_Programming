#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, w, b; cin >> n >> w >> b;
    while(n > 0) {
        int res = 1, cur_h = 0;
        vector<int> ht(w, -1);
        for(int i = 0; i < n; i++) {
            int h; cin >> h;
            vector<string> grid(h);
            for(int j = 0; j < h; j++) {
                cin >> grid[j];
            }
            int mx_h = 0, base = 0;
            vector<pair<int, int>> in(w, {-1, -1});
            for(int j = 0; j < w; j++) {
                for(int k = 0; k < h; k++) {
                    if(grid[k][j] == 'X') {
                        in[j].first = h - k - 1;
                    }
                }
                for(int k = h - 1; k >= 0; k--) {
                    if(grid[k][j] == 'X') {
                        in[j].second = h - k - 1;
                    }
                }
                base = max(base, ht[j] + 1 - in[j].first);
                mx_h = max(mx_h, in[j].second);
            }
            if(base + mx_h >= b) {
                cout << cur_h << " ";
                ++res, base = cur_h = 0;
                fill(ht.begin(), ht.end(), -1);
            }
            for(int j = 0; j < w; j++) {
                if(in[j].second != -1) {
                    ht[j] = max(ht[j], base + in[j].second);
                    cur_h = max(cur_h, ht[j] + 1);
                }
            }
        }
        cout << cur_h << '\n';
        cin >> n >> w >> b;
    }
}