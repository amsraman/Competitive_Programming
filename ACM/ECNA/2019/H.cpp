#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int a, b, c, d, e, f, g; cin >> a >> b >> c >> d >> e >> f >> g;
    vector<int> vols;
    for(int i = 1; 2 * i < min(a, b); i++) {
        vols.push_back(i * (a - 2 * i) * (b - 2 * i));
    }
    sort(vols.begin(), vols.end());
    reverse(vols.begin(), vols.end());
    int vol1 = vols[0], vol2 = vols[1], vol3 = vols[2];
    ll l = vol1 * vol2 / __gcd(vol1, vol2);
    l = l * vol3 / __gcd(l, 1LL * vol3);
    for(ll md = c;; md += vol1) {
        if(md % vol2 == d && md % vol3 == e) {
            cout << (g - md) / l * l + md << '\n';
            break;
        }
    }
}