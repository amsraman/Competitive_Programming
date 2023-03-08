#include <bits/stdc++.h>

using namespace std;

int main() {
    string a, b, ans; cin >> a >> b;
    int n = a.length(), m = b.length();
    for(int i = 0, j = 0; i < n || j < m;) {
        if(j == m || i < n && a[i] < b[j]) {
            ans += a[i++];
        } else {
            ans += b[j++];
        }
    }
    cout << ans << '\n';
}