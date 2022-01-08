#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, t[200000];

bool ok(ll x) {
    vector<ll> tmp(n);
    for(int i = 0; i < n; i++) {
        tmp[i] = t[i];
    }
    for(int i = 0; i < n - 1; i++) {
        if(2 * x < tmp[i]) {
            return false;
        }
        // Destroy as much as possible while still being able to move the rest
        ll mv = max(0LL, tmp[i] - x);
        tmp[i + 1] += 2 * mv;
    }
    return (tmp[n - 1] <= x);
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> t[i];
    }
    ll lb = 0, ub = 1e10;
    while(lb < ub) {
        ll mid = (lb + ub) / 2;
        if(ok(mid)) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    cout << ub << endl;
}
