#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m, k;
        ll s1 = 0, s2 = 0;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            s1 += a[i];
        }
        cin >> m;
        vector<int> b(m);
        for(int i = 0; i < m; i++) {
            cin >> b[i];
            s2 += b[i];
        }
        cin >> k;
        vector<ll> ba(k + 1, 0), bb(k + 1, 0);
        for(int i = 0; i < n; i++) {
            ll cur = 0;
            for(int j = i; j < n; j++) {
                cur += a[j];
                int sz = n - (j - i + 1);
                if(sz <= k) {
                    ba[sz] = max(ba[sz], s1 - cur);
                }
            }
        }
        for(int i = 0; i < m; i++) {
            ll cur = 0;
            for(int j = i; j < m; j++) {
                cur += b[j];
                int sz = m - (j - i + 1);
                if(sz <= k) {
                    bb[sz] = max(bb[sz], s2 - cur);
                }
            }
        }
        if(n <= k) {
            ba[n] = s1;
        }
        if(m <= k) {
            bb[m] = s2;
        }
        ll ans = 0;
        for(int i = 0; i <= k; i++) {
            if(i <= n && k - i <= m) {
                ans = max(ans, ba[i] + bb[k - i]);
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}