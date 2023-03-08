#include <bits/stdc++.h>

using namespace std;

int main() {
    string s; cin >> s;
    int n = s.length(), ans = n;
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            string sub = s.substr(i, j - i + 1);
            int mt = 0, len = sub.length(), lst = -1;
            for(int k = 0; k + len <= n; k++) {
                if(s.substr(k, len) == sub && k > lst) {
                    mt++, lst = k + len - 1;
                }
            }
            ans = min(ans, n - mt * len + mt + len);
        }
    }
    cout << ans << '\n';
}
