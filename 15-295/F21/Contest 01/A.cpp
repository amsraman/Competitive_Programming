#include <bits/stdc++.h>

using namespace std;

int n, a[100], minh = 0x3f3f3f3f;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(i > 0) {
            minh = min(minh, abs(a[i] - a[i - 1]));
        }
    }
    minh = min(minh, abs(a[0] - a[n - 1]));
    for(int i = 0; i < n; i++) {
        if(abs(a[(i + 1) % n] - a[i]) == minh) {
            cout << i + 1 << " " << 1 + (i + 1) % n << endl;
            return 0;
        }
    }
}