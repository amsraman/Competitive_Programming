#include <bits/stdc++.h>

using namespace std;

int t, n, m;

int main() {
    cin >> t;
    while(t--) {
        cin >> n >> m;
        int ans = 0;
        ++m;
        for(int i = 30; i >= 0; i--) {
            bool b1 = ((1 << i) & n);
            bool b2 = ((1 << i) & m);
            if(b1 ^ b2) {
                if(b2) {
                    ans ^= (1 << i);
                } else {
                    break;
                }
            }
        }
        cout << ans << endl;
    }
}