#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    int _ = 0;
    while(n > 0) {
        _++;
        vector<pair<int, int>> pts;
        for(int i = 0, x, y; i < n; i++) {
            cin >> x >> y;
            pts.emplace_back(x, y);
        }
        int res = 0;
        for(int i = 0; i < n; i++) {
            map<pair<int, int>, int> ct;
            for(int j = 0; j < n; j++) {
                pair<int, int> df = {pts[i].first - pts[j].first, pts[i].second - pts[j].second};
                if(df.first < 0) {
                    df.first *= -1, df.second *= -1;
                } else if(df.first == 0 && df.second < 0) {
                    df.second *= -1;
                }
                int g = __gcd(abs(df.first), abs(df.second));
                if(g > 0) {
                    df.first /= g, df.second /= g;
                }
                ++ct[df];
            }
            for(auto it: ct) {
                res = max(res, it.second + 1);
            }
        }
        if(res < 4) res = 0;
        cout << "Photo " << _ << ": " << res << " points eliminated\n";
        cin >> n;
    }
}