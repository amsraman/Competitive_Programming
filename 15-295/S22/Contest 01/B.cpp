#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, a[100000];
ll ans;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ans += a[i];
    }
    if(ans % 2 == 0) {
        cout << ans << '\n';
    } else {
        int mn = 0x3f3f3f3f;
        for(int i = 0; i < n; i++) {
            if(a[i] % 2 == 1 && a[i] < mn) {
                mn = a[i];
            }
        }
        cout << ans - mn << '\n';
    }
}