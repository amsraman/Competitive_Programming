#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, x, r, p, k;
ll mv[1000000], ans;
string reg;

int main() {
    cin >> n >> x >> r >> p >> k >> reg;
    ans = 1LL * x * n;
    for(int i = 0; i < n; i++) {
        if(reg[i] == '1') {
            mv[i] = 1LL * (p + r) * (n - i);
            ans -= 1LL * r * (n - i);
        } else {
            mv[i] = 1LL * p * (n - i);
        }
    }
    sort(mv, mv + n);
    for(int i = 0; i < k; i++) {
        ans += mv[n - i - 1];
    }
    cout << ans << endl;
}