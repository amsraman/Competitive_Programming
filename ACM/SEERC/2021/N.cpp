#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, a[200001], b[200001];
ll ans = 0;
bool pos = true;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i <= n; i++) {
        cin >> b[i];
    }
    for(int i = n; i > 0; i--) {
        int df = (max(0, b[i] - a[i]) + 1) / 2;
        ans += df, a[i - 1] -= df;
    }
    if(a[0] < b[0]) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
}