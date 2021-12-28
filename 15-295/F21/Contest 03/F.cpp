#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll n;

int ask(ll x) {
    cout << "? " << x << endl;
    int ret;
    cin >> ret;
    return ret;
}

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        ll lb = 1, ub = n - 1, cur = n, delta = 0, ans = n;
        bool move = true;
        // Simulate worst-case binary search to "push back" start as much as necessary
        while(lb <= ub) {
            ll mid = (lb + ub) / 2;
            delta += (move ? mid : -mid);
            cur = min(cur, n - delta);
            lb = mid + 1;
            move ^= 1;
        }
        lb = 1, ub = n - 1, move = true;
        ask(cur);
        while(lb <= ub) {
            ll mid = (lb + ub) / 2;
            cur += (move ? mid : -mid);
            if(ask(cur) == 1) {
                ans = mid;
                ub = mid - 1;
            } else {
                lb = mid + 1;
            }
            move ^= 1;
        }
        cout << "= " << ans << endl;
    }
}