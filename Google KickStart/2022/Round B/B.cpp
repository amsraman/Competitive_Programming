#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

bool isPalin(ll x) {
    vector<int> d;
    while(x > 0) {
        d.push_back(x % 10), x /= 10;
    }
    for(int i = 0, j = (int) d.size() - 1; i < j; i++, j--) {
        if(d[i] != d[j]) {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        ll a;
        cin >> a;
        set<ll> factors;
        for(int i = 1; 1LL * i * i <= a; i++) {
            if(a % i == 0) {
                factors.insert(i);
                factors.insert(a / i);
            }
        }
        int ans = 0;
        for(ll f: factors) {
            ans += isPalin(f);
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}