#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, s, a[100000];
ll tmp[100000];

bool ok(ll x) {
    for(int i = 0; i < n; i++) {
        tmp[i] = a[i] + (ll) x * (i + 1);
    }
    sort(tmp, tmp + n);
    ll cost = 0;
    for(int i = 0; i < x; i++) {
        cost += tmp[i];
    }
    return (cost <= s);
}

int main() {
    cin >> n >> s;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll lb = 0, ub = n;
    while(lb < ub) {
        int mid = (lb + ub + 1) / 2;
        if(ok(mid)) {
            lb = mid;
        } else {
            ub = mid - 1;
        }
    }
    ll cost = 0;
    for(int i = 0; i < n; i++) {
        tmp[i] = a[i] + (ll) ub * (i + 1);
    }
    sort(tmp, tmp + n);
    for(int i = 0; i < ub; i++) {
        cost += tmp[i];
    }
    cout << ub << " " << cost << endl;
}