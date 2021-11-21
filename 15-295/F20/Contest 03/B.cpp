#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n;
ll k, c[300000], tmp[300000], tot;

bool ok(ll x) {
    for(int i = 0; i < n; i++) {
        tmp[i] = c[i];
    }
    ll rows_taken = 0;
    int cur = 0;
    while(rows_taken < k && cur < n) {
        if(cur < n - 1 && tmp[cur] + tmp[cur + 1] < x) {
            ++cur;
        } else if(cur < n - 1 && tmp[cur] < x) {
            ++rows_taken;
            tmp[cur + 1] += (tmp[cur] - x);
            ++cur;
        } else {
            rows_taken += tmp[cur] / x;
            tmp[cur] %= x;
            if(tmp[cur] == 0 || cur == n - 1) {
                ++cur;
            }
        }
    }
    return (rows_taken >= k);
}

int main() {
    cin >> t;
    while(t--) {
        cin >> n >> k;
        tot = 0;
        for(int i = 0; i < n; i++) {
            cin >> c[i];
            tot += c[i];
        }
        ll lb = 1, ub = tot / k;
        while(lb < ub) {
            ll mid = (lb + ub + 1) / 2;
            if(ok(mid)) {
                lb = mid;
            } else {
                ub = mid - 1;
            }
        }
        cout << ub * k << endl;
    }
}