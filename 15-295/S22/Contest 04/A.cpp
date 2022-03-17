#include <bits/stdc++.h>

using namespace std;

int t, n, a[100000];

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int tot = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] > 1) {
                break;
            }
            ++tot;
        }
        tot = min(tot, n - 1);
        cout << ((tot & 1) ? "Second" : "First") << '\n';
    }
}