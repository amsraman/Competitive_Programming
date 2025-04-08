#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n; cin >> n;
    int _ = 0;
    while(n > 0) {
        _++;
        auto in_rectangle = [](int x, int y) {
            if(x > y) swap(x, y);
            // 1 * (y - x + 1) + 2 * (y - x + 2) + ... + x * y
            return 1LL * x * (x + 1) * (2 * x + 1) / 6 + 1LL * x * (x + 1) * (y - x) / 2;
        };
        ll ans = 0;
        vector<tuple<int, int, int, int>> rects;
        for(int i = 0; i < n; i++) {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            if(x1 > x2) swap(x1, x2);
            if(y1 > y2) swap(y1, y2);
            rects.emplace_back(x1, y1, x2, y2);
            ans += in_rectangle(x2 - x1, y2 - y1);
        }
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                auto [x11, y11, x12, y12] = rects[i];
                auto [x21, y21, x22, y22] = rects[j];
                if(x21 == x12 || x11 == x22) {
                    int dy = max(0, min(y12, y22) - max(y11, y21) - 2);
                    ans += in_rectangle(x22 + x12 - x21 - x11, dy) - in_rectangle(x22 - x21, dy) - in_rectangle(x12 - x11, dy);
                }
                if(y21 == y12 || y11 == y22) {
                    int dx = max(0, min(x12, x22) - max(x11, x21) - 2);
                    ans += in_rectangle(dx, y22 + y12 - y21 - y11) - in_rectangle(dx, y22 - y21) - in_rectangle(dx, y12 - y11);
                }
            }
        }
        cout << "Case " << _ << ": " << ans << '\n';
        cin >> n;
    }
}