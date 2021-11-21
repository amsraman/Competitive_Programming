#include <bits/stdc++.h>

using namespace std;

int t, a[4];

int main() {
    cin >> t;
    while(t--) {
        for(int i = 0; i < 4; i++) {
            cin >> a[i];
        }
        sort(a, a + 4);
        cout << a[0] * a[2] << endl;
    }
}