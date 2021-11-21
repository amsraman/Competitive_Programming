#include <bits/stdc++.h>

using namespace std;

int t, n, q, num[2];
bool pre[100], suf[100];
string s;

int main() {
    cin >> t;
    while(t--) {
        cin >> n >> q >> s;
        num[0] = num[1] = 0;
        for(int i = 0; i < n; i++) {
            pre[i] = num[(s[i] - '0')] > 0;
            ++num[(s[i] - '0')];
        }
        num[0] = num[1] = 0;
        for(int i = n - 1; i >= 0; i--) {
            suf[i] = num[(s[i] - '0')] > 0;
            ++num[(s[i] - '0')];
        }
        for(int i = 0, l, r; i < q; i++) {
            cin >> l >> r;
            cout << ((pre[l - 1] || suf[r - 1]) ? "YES" : "NO") << endl;
        }
    }
}