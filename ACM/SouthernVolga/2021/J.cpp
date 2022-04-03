#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k, x, a[2000], b[2000], c[2000], d[2000];
ll ans = -0xfffffffffffffff;
bool dp[2000][5];

int main() {
    cin >> n >> k >> x;
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }
    dp[0][k] = true;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2 * k + 1; j++) {
            if(dp[i][j]) {
                ll c1 = x + j - k, c2 = x + j - k;
                int n1 = i + 1, n2 = i + 1;
                c1 += (c[i] ? a[i] : -b[i]);
                c2 += (d[i] ? a[i] : -b[i]);
                while(n1 < n && abs(c1 - x) > k) {
                    if(c1 < x - k) {
                        c1 += (c[n1] ? a[n1] : -b[n1]);
                    } else {
                        c1 += (d[n1] ? a[n1] : -b[n1]);
                    }
                    ++n1;
                }
                while(n2 < n && abs(c2 - x) > k) {
                    if(c2 < x - k) {
                        c2 += (c[n2] ? a[n2] : -b[n2]);
                    } else {
                        c2 += (d[n2] ? a[n2] : -b[n2]);
                    }
                    ++n2;
                }
                if(n1 == n) {
                    ans = max(ans, c1);
                } else {
                    dp[n1][c1 - x + k] = true;
                }
                if(n2 == n) {
                    ans = max(ans, c2);
                } else {
                    dp[n2][c2 - x + k] = true;
                }
            }
        }
    }
    cout << ans << endl;
}