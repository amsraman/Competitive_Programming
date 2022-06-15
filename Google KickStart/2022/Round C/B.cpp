#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, x, y;
        cin >> n >> x >> y;
        ll sum = n * (n + 1) / 2;
        cout << "Case #" << _ << ": ";
        auto pos = [](int x, int y) {
            int s = x * (x + 1) / 2;
            return (y >= 0 && y <= s);
        };
        if((sum * x) % (x + y) != 0) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            int targ = 1LL * sum * x / (x + y);
            if(!pos(n, targ)) {
                cout << "IMPOSSIBLE" << endl;
            } else {
                cout << "POSSIBLE" << endl;
                vector<int> ans;
                for(int i = n; i >= 1; i--) {
                    if(pos(i - 1, targ - i)) {
                        targ -= i;
                        ans.push_back(i);
                    }
                }
                reverse(ans.begin(), ans.end());
                cout << ans.size() << endl;
                for(int a: ans) {
                    cout << a << " ";
                }
                cout << endl;
            }
        }
    }
}