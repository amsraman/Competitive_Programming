#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, a[200000];
ll dp[200001];

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for(int i = 0; i <= n; i++) {
            dp[i] = 0;
        }
        for(int i = 0; i < n; i++) {
            dp[min(n, i + a[i])] = max(dp[min(n, i + a[i])], dp[i] + a[i]);
        }
        cout << dp[n] << endl;
    }
}