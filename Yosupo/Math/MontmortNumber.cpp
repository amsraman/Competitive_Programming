// 74 ms
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, d1 = 0, d2 = 1; cin >> n >> m;
    cout << d1 << " ";
    for(int i = 1, nxt; i < n; i++) {
        cout << d2 << " ";
        nxt = 1LL * (i + 1) * (d1 + d2) % m, d1 = d2, d2 = nxt;
    }
    cout << '\n';
}