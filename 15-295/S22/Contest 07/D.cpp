#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t;
ll k, fact[19];

ll ncr(int n, int r) {
    if(r < 0 || r > n) {
        return 0;
    }
    return fact[n] / fact[n - r] / fact[r];
}

int main() {
    fact[0] = 1;
    for(int i = 1; i < 19; i++) {
        fact[i] = fact[i - 1] * i;
    }
    cin >> t;
    while(t--) {
        cin >> k;
        vector<int> d;
        for(int i = 2; k > 0; i++) {
            d.push_back(k % i);
            k /= i;
        }
        sort(d.begin(), d.end());
        vector<pair<int, int>> grp;
        int tot = d.size();
        for(int i = 0, j = 0; i < tot; i++) {
            ++j;
            if(i + 1 == tot || d[i] < d[i + 1]) {
                grp.push_back({d[i], j});
                j = 0;
            }
        }
        ll ans = 1;
        for(int i = grp.size() - 1; i >= 0; i--) {
            ans *= ncr(tot + 1 - max(1, grp[i].f), grp[i].s);
            tot -= grp[i].s;
        }
        if(grp[0].f == 0) {
            ll sub = 1;
            tot = d.size() - 1, --grp[0].s;
            for(int i = grp.size() - 1; i >= 0; i--) {
                sub *= ncr(tot + 1 - max(1, grp[i].f), grp[i].s);
                tot -= grp[i].s;
            }
            ans -= sub;
        }
        cout << ans - 1 << endl;
    }
}