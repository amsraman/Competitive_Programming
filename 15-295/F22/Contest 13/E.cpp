#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        int x, y; cin >> x >> y;
        vector<vector<int>> rect(4);
        for(int i = 0, k; i < 4; i++) {
            cin >> k; rect[i].resize(k);
            for(int j = 0; j < k; j++) {
                cin >> rect[i][j];
            }
            sort(rect[i].begin(), rect[i].end());
        }
        swap(rect[1], rect[2]);
        ll ans = 0;
        vector<int> coords = {y, x};
        for(int i = 0; i < 4; i++) {
            int sz = rect[i].size(), mx = rect[i][sz - 1] - rect[i][0];
            ans = max(ans, 1LL * mx * coords[i % 2]);
        }
        cout << ans << '\n';
    }
}