#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n;
        cin >> n;
        vector<string> colors(n);
        vector<int> d(n), u(n);
        vector<tuple<string, int, int>> ord1(n);
        vector<array<int, 3>> ord2(n);
        for(int i = 0; i < n; i++) {
            cin >> colors[i] >> d[i] >> u[i];
            ord1[i] = {colors[i], u[i], i};
            ord2[i] = {d[i], u[i], i};
        }
        int ans = 0;
        sort(ord1.begin(), ord1.end());
        sort(ord2.begin(), ord2.end());
        for(int i = 0; i < n; i++) {
            ans += get<2>(ord1[i]) == ord2[i][2];
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}