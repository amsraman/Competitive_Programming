#include <bits/stdc++.h>

using namespace std;

int t, n, m, a, b;

int main() {
    freopen("traffic_control_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> m >> a >> b;
        cout << "Case #" << _ << ": ";
        if(min(a, b) < n + m - 1) {
            cout << "Impossible" << endl;
        } else {
            cout << "Possible" << endl;
            cout << a - n - m + 2 << " ";
            for(int i = 1; i < m - 1; i++) {
                cout << 1 << " ";
            }
            cout << b - n - m + 2 << endl;
            for(int i = 1; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    cout << ((j == 0 || j == m - 1 || i == n - 1) ? 1 : 1000) << " ";
                }
                cout << endl;
            }
        }
    }
}