#include <bits/stdc++.h>

using namespace std;

int t, n, m, a, b, s[200000], stalling_time;

bool ok(int x) {
    int mx = 0;
    for(int i = x - 1; i >= 0; i--) {
        mx = max(mx, s[i] + x - i - 1);
    }
    return (mx < stalling_time);
}

int main() {
    cin >> t;
    while(t--) {
        cin >> n >> m >> a >> b;
        for(int i = 0; i < m; i++) {
            cin >> s[i];
        }
        sort(s, s + m);
        stalling_time = b - 1;
        if(a > b) {
            stalling_time = n - b;
        }
        int lb = 0, ub = min(m, abs(a - b) - 1);
        while(lb < ub) {
            int mid = (lb + ub + 1) / 2;
            if(ok(mid)) {
                lb = mid;
            } else {
                ub = mid - 1;
            }
        }
        cout << ub << endl;
    }
}