#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int ang;
        cin >> ang;
        int arc = 360 - 2 * ang;
        if(360 % arc == 0) {
            cout << 720 / __gcd(360, 2 * ang);
        } else {
            cout << 360 / __gcd(360, 2 * ang);
        }
        cout << endl;
    }
}