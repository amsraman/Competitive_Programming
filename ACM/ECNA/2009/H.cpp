#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    for(int _ = 1; n > 0; _++) {
        vector<tuple<int, int, int, int>> windows;
        for(int i = 0, r, c, w, h; i < n; i++) {
            cin >> r >> c >> w >> h;
            windows.emplace_back(r, c, w, h);
        }
        int m; cin >> m;
        cout << "Desktop " << _ << ":\n";
        for(int i = 0, cr, cc; i < m; i++) {
            cin >> cr >> cc;
            string res = "background";
            for(int j = 0; j < n; j++) {
                auto [r, c, w, h] = windows[j];
                if(cr >= r && cr < r + h && cc >= c && cc < c + w) {
                    res = "window " + to_string(j + 1);
                }
            }
            cout << res << '\n';
        }
        cin >> n;
    }
}