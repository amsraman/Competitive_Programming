#include <bits/stdc++.h>

using namespace std;

int n, m, a[1000001], tot;

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        tot += a[i];
    }
    for(int i = 0, q; i < m; i++) {
        cin >> q;
        bool ans = false;
        if(q <= tot) {
            int pf = 0, sf = tot;
            for(int j = 0, k = 0; j <= n; j++) {
                while(k < n && (k <= j || (pf + sf) > q)) {
                    sf -= a[k], ++k;
                }
                if(pf + sf == q) {
                    ans = true;
                }
                pf += a[j];
            }
        }
        cout << (ans ? "Yes\n" : "No\n");
    }
}