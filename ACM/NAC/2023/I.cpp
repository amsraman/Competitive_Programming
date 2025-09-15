#include <bits/stdc++.h>
typedef __int128_t ll;

using namespace std;

int main() {
    long long x; cin >> x;
    int ans = -1;
    vector<ll> prod(1e6 + 1, 1);
    for(int i = 1; i <= 1e6; i++) {
        for(int j = i; j <= 1e6; j += i) {
            if(j <= 1e6 * x / prod[j]) {
                prod[j] *= j;
            }
        }
        if(prod[i] == x) {
            ans = i;
            break;
        }
    }
    auto is_prime = [](int x) {
        for(int i = 2; i * i <= x; i++) {
            if(x % i == 0) {
                return false;
            }
        }
        return x > 1;
    };
    int sq = sqrt(x);
    if(1LL * sq * sq == x && is_prime(sq)) ans = sq;
    cout << ans << '\n';
}