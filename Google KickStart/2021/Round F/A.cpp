#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, l[500000], r[500000];
string trsh;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> trsh;
        ll ans = 0;
        l[0] = (trsh[0] == '1' ? 0 : 0x3f3f3f3f), r[n - 1] = (trsh[n - 1] == '1' ? 0 : 0x3f3f3f3f);
        for(int i = 1; i < n; i++) {
            if(trsh[i] == '1') {
                l[i] = 0;
            } else {
                l[i] = l[i - 1] + 1;
            }
        }
        for(int i = n - 2; i >= 0; i--) {
            if(trsh[i] == '1') {
                r[i] = 0;
            } else {
                r[i] = r[i + 1] + 1;
            }
        }
        for(int i = 0; i < n; i++) {
            ans += min(l[i], r[i]);
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}