#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll a, b, x;

int main() {
    cin >> t;
    while(t--) {
        cin >> a >> b >> x;
        bool ok = false;
        if(a < b) {
            swap(a, b);
        }
        while(b > 0) {
            if(x <= a && (a - x) % b == 0) {
                ok = true;
            }
            a %= b;
            if(a < b) {
                swap(a, b);
            }
        }
        cout << (ok ? "YES" : "NO") << endl;
    }
}
