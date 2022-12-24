#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> t(n);
    for(int i = 0; i < n; i++) {
        cin >> t[i];
    }
    ll ans = 0;
    vector<vector<ll>> num(n + 1, vector<ll>(10, 0));
    num[0][0] = 1;
    for(int i = 0; i < n; i++) {
        ll bad_count = 0;
        for(int j = 0; j < t[i]; j++) {
            for(int pvd = 0; pvd < 10; pvd++) {
                int worst_case = 10 * pvd + max(j % 10, j / 10);
                if(worst_case >= t[i]) {
                    bad_count += num[i][pvd];
                } else {
                    num[i + 1][j % 10] += num[i][pvd];
                }
            }
        }
        for(int j = i + 1; j < n; j++) {
            bad_count *= t[j];
        }
        ans += bad_count;
    }
    cout << ans << endl;
}