#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k;

int main() {
    cin >> n >> k;
    ll lb = 0, ub = 1e5;
    while(lb < ub) {
        ll mid = (lb + ub) / 2;
        if(mid * (mid + 1) / 2 + mid - n >= k) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    cout << ub * (ub + 1) / 2 - k << endl;
}