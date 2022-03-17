#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, m, p[100000], c[100000];

bool ok(ll x) {
    ll tot = 0;
    for(int i = 0; i < n; i++) {
        tot += max(0LL, x * p[i] - c[i]);
        if(tot >= m) {
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> p[i] >> c[i];
    }
    ll lb = 0, ub = 2e9;
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