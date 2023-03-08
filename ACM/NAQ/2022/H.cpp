#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n, s, k; cin >> n >> s >> k;
    vector<int> x(n);
    for(int i = 0; i < n; i++) {
        cin >> x[i]; x[i] *= 2;
    }
    sort(x.begin(), x.end());
    bool bad = false; ll ans = 0; int pv = -1e8;
    for(int i = 0; i < n; i++) {
        int go = k;
        go = min(go, x[i] - pv);
        if(i < n - 1) {
            if(x[i] + 2 * s > x[i + 1]) bad = true;
            go = min(go, x[i + 1] - s - x[i]);
        }
        ans += go; pv = x[i] + go;
    }
    cout << (bad ? -1 : ans) << '\n';
}