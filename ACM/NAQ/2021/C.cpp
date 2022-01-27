#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll n;

bool isPrime(int x) {
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n;
    ll ans1 = 1, ans2 = 1;
    for(ll cur = 1, p = 2; cur <= n; p++) {
        while(!isPrime(p)) {
            ++p;
        }
        if(cur <= n / p) {
            cur *= p, ans1 *= (p - 1), ans2 *= p;
            ll g = __gcd(ans1, ans2);
            ans1 /= g, ans2 /= g;
        } else {
            break;
        }
    }
    ans1 = ans2 - ans1;
    cout << ans1 << '/' << ans2 << endl;
}