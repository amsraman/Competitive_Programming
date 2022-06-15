// 174 ms
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<ll> ps(n + 1, 0);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ps[i + 1] = ps[i] + a[i];
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << ps[r] - ps[l] << '\n';
    }
}