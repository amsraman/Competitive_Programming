#include <bits/stdc++.h>

using namespace std;

int main() {
    string n;
    int m;
    cin >> n >> m;
    int sz = n.length(), ans = m;
    vector<int> p10(sz + 1);
    p10[0] = 1;
    for(int i = 1; i <= sz; i++) {
        p10[i] = (1LL * p10[i - 1] * 10) % m;
    }
    vector<int> pf(sz, 0), sf(sz, 0);
    for(int i = 1; i < sz; i++) {
        pf[i] = ((n[i - 1] - '0') + (1LL * 10 * pf[i - 1]) % m) % m;
    }
    sf[sz - 1] = n[sz - 1] - '0';
    for(int i = sz - 2; i >= 0; i--) {
        sf[i] = (sf[i + 1] + (1LL * p10[sz - i - 1] * (n[i] - '0')) % m) % m;
    }
    for(int i = 0; i < sz; i++) {
        if(n[i] != '0') {
            int md = (pf[i] + (1LL * sf[i] * p10[i]) % m) % m;
            ans = min(ans, md);
        }
    }
    cout << ans << endl;
}