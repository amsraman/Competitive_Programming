#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<ll> s(n); ll g = 0;
        for(int i = 0; i < n; i++) {
            cin >> s[i]; g = __gcd(g, s[i]);
        }
        int no = 0, ne = 0;
        for(int i = 0; i < n; i++) {
            if(n & 1) s[i] /= g;
            no += (s[i] & 1), ne += (s[i] & 1 ^ 1);
        }
        cout << (ne > 0) << '\n';
    }
}