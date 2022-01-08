#include <bits/stdc++.h>

using namespace std;

int t, x, y;

int main() {
    cin >> t;
    while(t--) {
        cin >> x >> y;
        if((x + y) % 2 == 1) {
            cout << "-1 -1" << endl;
        } else {
            cout << x / 2 << " " << (y + 1) / 2 << endl;
        }
    }
}
