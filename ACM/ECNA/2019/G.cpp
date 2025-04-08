#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n, m, a, c, x0; cin >> n >> m >> a >> c >> x0;
    vector<int> ar(n);
    for(int i = 0; i < n; i++) {
        ar[i] = x0 = ((1LL * x0 * a) % m + c) % m;
    }
    int res = 0;
    for(int i = 0; i < n; i++) {
        int lb = 0, ub = n - 1;
        bool ok = false;
        while(lb <= ub) {
            int mid = (lb + ub) / 2;
            if(ar[mid] == ar[i]) {
                ok = true;
                break;
            } else if(ar[mid] < ar[i]) {
                lb = mid + 1;
            } else {
                ub = mid - 1;
            }
        }
        res += ok;
    }
    cout << res << '\n';
}