#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int a, b, n, m; cin >> a >> b >> n >> m;
        ll res = 0;
        while(true) {
            res += 1LL * a * b;
            if(a == n && b == m) break;
            if(b == m || (a < n && a <= b)) {
                ++a;
            } else {
                ++b;
            }
        }
        cout << res << '\n';
    }
}
/*

*/