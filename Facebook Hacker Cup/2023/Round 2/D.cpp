#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int main() {
    ifstream cin("tower_rush_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, k, d; cin >> n >> k >> d;
        vector<int> h(n), ct(1e6 + 1, 0);
        for(int i = 0; i < n; i++) {
            cin >> h[i]; ++ct[h[i]];
        }
        for(int i = 1; i <= 1e6; i++) {
            for(int j = 2 * i; j <= 1e6; j += i) {
                ct[i] += ct[j];
            }
        }
        int ans = 0;
        for(int i = 1e6; i >= 1; i--) {
            int num = ct[i];
            ct[i] = 1;
            for(int j = 0; j < k; j++) {
                ct[i] = (1LL * ct[i] * (num - j)) % mod;
            }
            for(int j = 2 * i; j <= 1e6; j += i) {
                ct[i] = (ct[i] - ct[j] + mod) % mod;
            }
            if(d % i == 0) ans = (ans + ct[i]) % mod;
        }
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}