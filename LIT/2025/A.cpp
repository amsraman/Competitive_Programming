#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> p(n), ip(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i]; --p[i];
        ip[p[i]] = i;
    }
    int q; cin >> q;
    for(int i = 0, x, y; i < q; i++) {
        cin >> x >> y; --x, --y;
        swap(ip[x], ip[y]);
    }
    for(int i = 0; i < n; i++) {
        p[ip[i]] = i + 1;
    }
    for(int i = 0; i < n; i++) {
        cout << p[i] << " ";
    }
    cout << '\n';
}