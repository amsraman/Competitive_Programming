#include <bits/stdc++.h>

using namespace std;

int main() {
    string c, s, ans; cin >> c >> s;
    int n = c.length(), m = s.length();
    for(int i = 0; i < n; i++) {
        char pv = (i < m ? s[i] : ans[i - m]);
        ans += char('A' + (c[i] - pv + 26) % 26);
    }
    cout << ans << '\n';
}
