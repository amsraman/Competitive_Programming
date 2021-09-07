#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int q, n, k, a[300000], t[300000], tmp[300000], l[300000], r[300000];

int main() {
    cin >> q;
    while(q--) {
        cin >> n >> k;
        for(int i = 0; i < k; i++) {
            cin >> a[i];
        }
        for(int i = 0; i < n; i++) {
            tmp[i] = INF;
        }
        for(int i = 0; i < k; i++) {
            cin >> t[i];
            tmp[a[i] - 1] = t[i];
        }
        int ct = INF;
        for(int i = 0; i < n; i++) {
            ct = min(ct, tmp[i]);
            l[i] = ct;
            ++ct;
        }
        ct = INF;
        for(int i = n - 1; i >= 0; i--) {
            ct = min(ct, tmp[i]);
            r[i] = ct;
            ++ct;
        }
        for(int i = 0; i < n; i++) {
            cout << min(l[i], r[i]) << " ";
        }
        cout << endl;
    }
}