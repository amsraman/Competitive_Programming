#include <bits/stdc++.h>

using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        long long n, d; cin >> n >> d; // is this just ceil(log_{d+1}(n))
        __int128_t acc = 1;
        int ans = 0;
        while(acc < n) {
            acc *= (d + 1), ++ans;
        }
        cout << ans << '\n';
    }
}