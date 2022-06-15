#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    if(n < 3) {
        cout << -1 << endl;
    } else if(n & 1) {
        cout << (1LL * n * n - 1) / 2 << " " << (1LL * n * n + 1) / 2 << endl;
    } else {
        cout << (1ll * n * n / 2 - 2) / 2 << " " << (1LL * n * n / 2 + 2) / 2 << endl;
    }
}