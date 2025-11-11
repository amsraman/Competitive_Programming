#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<ll> num(n + 1, 0); ll res = 0;
        for(int i = n; i > 0; i--) {
            int mx = n / i;
            mx = (mx + 1) / 2;
            num[i] = 2LL * mx * mx - mx;
            for(int j = 3 * i; j <= n; j += 2 * i) {
                num[i] -= num[j];
            }
            res += num[i];
        }
        cout << res << '\n';
    }
}
/*
(1, 1): win
(1, 2): lose
(2, 1): lose
(2, 2): win
(1, 3): win
(2, 3): win
(3, 3): win
(3, 1): win
(3, 2): win

cody wins if max / g is odd
*/