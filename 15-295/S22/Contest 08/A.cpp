#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int m;
        ll n, p2 = 1;
        cin >> m >> n;
        for(int i = 0; i < m; i++) {
            p2 *= 2;
        }
        if(m == 1 && n == 0) {
            cout << "1\n";
        } else if(m == 1) {
            cout << "2\n";
        } else if(n == 0) {
            cout << p2 << '\n';
        } else {
            cout << p2 - 1 << '\n';
        }
    }
}