#include <bits/stdc++.h>

using namespace std;

int n, co[26];
string st[100];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> st[i];
        ++co[st[i][0] - 'a'];
    }
    int ans = 0;
    for(int i = 0; i < 26; i++) {
        int g1 = (co[i] / 2), g2 = (co[i] + 1) / 2;
        ans += g1 * (g1 - 1) / 2 + g2 * (g2 - 1) / 2;
    }
    cout << ans << endl;
}