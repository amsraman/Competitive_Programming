// 781 ms
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int q;
    map<ll, ll> arr;
    cin >> q;
    while(q--) {
        int type;
        cin >> type;
        if(type == 0) {
            ll k, v;
            cin >> k >> v;
            arr[k] = v;
        } else {
            ll k;
            cin >> k;
            cout << arr[k] << '\n';
        }
    }
}