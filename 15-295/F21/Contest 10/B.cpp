#include <bits/stdc++.h>

using namespace std;

int t, n, ans;
string s;

int main() {
    cin >> t;
    while(t--) {
        cin >> s;
        n = s.length(), ans = 0;
        for(int i = 1; i < n; i++) {
            if(s[i] == s[i - 1] || (i > 1 && s[i] == s[i - 2])) {
                ++ans;
                s[i] = '$';
            }
        }
        cout << ans << endl;
    }
}