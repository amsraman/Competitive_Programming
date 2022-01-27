#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, a;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n;
        a = -1;
        for(int i = 2; i * i <= n; i++) {
            if(n % i == 0) {
                a = n / i;
                break;
            }
        }
        if(a == -1) {
            cout << 1 << " " << n - 1 << '\n';
        } else {
            cout << a << " " << n - a << '\n';
        }
    }
}

// a * (n - a) / gcd(n, a) is maximized