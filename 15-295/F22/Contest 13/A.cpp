#include <bits/stdc++.h> // why am i so bad
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int g, a; ll n; cin >> g >> a >> n;
    vector<int> guns(g), armour(a);
    for(int i = 0; i < g; i++) {
        cin >> guns[i];
    }
    for(int i = 0; i < a; i++) {
        cin >> armour[i];
    }
    sort(guns.begin(), guns.end()); sort(armour.begin(), armour.end());
    auto f = [&](int x) {
        ll ret = 0;
        for(int i = 0; i < g; i++) {
            int num = lower_bound(armour.begin(), armour.end(), x - guns[i] + 1) - armour.begin();
            ret += num;
        }
        return ret;
    };
    int lb = 0, ub = 4e6;
    while(lb < ub) { // minimum cost such that >= n are generated
        int mid = (lb + ub) / 2;
        if(f(mid) >= n) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    vector<ll> ps(a + 1, 0); ll ans = 0;
    for(int i = 1; i <= a; i++) {
        ps[i] = ps[i - 1] + armour[i - 1];
    }
    for(int i = 0; i < g; i++) {
        int ind = lower_bound(armour.begin(), armour.end(), ub - guns[i] + 1) - armour.begin();
        ans += ps[ind] + 1LL * ind * guns[i];
    }
    cout << ans - 1LL * ub * (f(ub) - n) << '\n';
}