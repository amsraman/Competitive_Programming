#include <bits/stdc++.h>

using namespace std;

int t, n, a;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> a;
        cout << "Case #" << _ << ": ";
        if(a < n - 2) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << "POSSIBLE" << endl;
            for(int i = (n + 1) / 2 - 2; i >= 0; i--) {
                cout << i % 2 << " " << i << endl;
            }
            for(int i = 0; i < (n + 1) / 2 - 1; i++) {
                cout << 1 + i % 2 << " " << i << endl;
            }
            int diff = a - n + 2;
            if(n % 4 == 0) {
                cout << 2 + diff << " " << (n / 2 - 1) << endl;
                cout << 1 << " " << (n / 2 - 1) << endl;
            } else if(n % 4 == 1) {
                cout << 1 << " " << (n / 2) + diff << endl;
            } else if(n % 4 == 2) {
                cout << 1 + diff << " " << (n / 2 - 1) << endl;
                cout << 0 << " " << (n / 2 - 1) << endl;
            } else {
                cout << 1 << " " << (n / 2) + diff << endl;
            }
        }
    }
}