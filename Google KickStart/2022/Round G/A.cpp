#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int m, n, p;
        cin >> m >> n >> p;
        vector<vector<int>> s(m, vector<int>(n));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                cin >> s[i][j];
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++) {
            int mx = 0;
            for(int j = 0; j < m; j++) {
                mx = max(mx, s[j][i]);
            }
            ans += mx - s[p - 1][i];
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}