#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, k;
ll x;

ll num(int x, int y) {
    if(y >= x) {
        int tmp = y - x;
        // x -> tmp
        return ((ll) x * (x - 1) / 2) + (ll) (2 * x - tmp) * (tmp + 1) / 2;
    }
    return ((ll) y * (y + 1)) / 2;
}

int main() {
    cin >> t;
    while(t--) {
        cin >> k >> x;
        ll lb = 0, ub = 2 * k - 1;
        while(lb < ub) {
            ll mid = (lb + ub) / 2;
            if(num(k, mid) < x) {
                lb = mid + 1;
            } else {
                ub = mid;
            }
        }
        cout << ub << endl;
    }
}
