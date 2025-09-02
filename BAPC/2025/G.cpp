#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n, m; cin >> n >> m;
    map<string, int> ct; ll res = 0;
    for(int i = 0; i < n; i++) {
        string cur = ""; char c;
        for(int j = 0; j < m * m; j++) {
            cin >> c; cur += c;
        }
        res += ct[cur]++;
    }
    string zer = "";
    for(int i = 0; i < m * m; i++) zer += ".";
    res += 1LL * ct[zer] * (n - ct[zer]);
    cout << res << '\n';
}