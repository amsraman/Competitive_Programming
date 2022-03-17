#include <bits/stdc++.h>

using namespace std;

int t, n, k;

int main() {
    cin >> t;
    while(t--) {
        cin >> n >> k;
        int ex = n % k;
        for(int i = 0; i < k; i++) {
            if(i < ex) {
                cout << char('a' + i);
            }
            for(int j = 0; j < n / k; j++) {
                cout << char('a' + i);
            }
        }
        cout << '\n';
    }
}