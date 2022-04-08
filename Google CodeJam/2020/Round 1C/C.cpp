#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t, n, d;
ll a[10000];

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> d;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        set<pair<ll, int>> fs;
        vector<pair<ll, int>> fv;
        for(int i = 0; i < n; i++) {
            for(int j = 1; j <= d; j++) {
                ll g = __gcd(a[i], 1LL * j);
                fs.insert({a[i] / g, j / g});
            }
        }
        for(pair<ll, int> f: fs) {
            fv.push_back(f);
        }
        sort(fv.begin(), fv.end(), [](pair<ll, int> f1, pair<ll, int> f2) {
            return 1LL * f2.s * f1.f < 1LL * f2.f * f1.s;
        });
        int lb = 0, ub = fv.size() - 1;
        while(lb < ub) {
            int mid = (lb + ub + 1) / 2;
            ll num_ok = 0;
            for(int i = 0; i < n; i++) {
                num_ok += 1LL * a[i] * fv[mid].s / fv[mid].f;
            }
            if(num_ok < d) {
                ub = mid - 1;
            } else {
                lb = mid;
            }
        }
        pair<ll, int> bst = fv[ub];
        map<pair<ll, int>, multiset<int>> sts;
        map<pair<ll, int>, ll> tot;
        for(int i = 0; i < n; i++) {
            for(int j = 1; j <= d; j++) {
                ll g = __gcd(a[i], 1LL * j);
                pair<ll, int> f = {a[i] / g, j / g};
                sts[f].insert(j);
                tot[f] += j;
                while(tot[f] > d) {
                    ll lst = *(--sts[f].end());
                    sts[f].erase(sts[f].find(lst));
                    tot[f] -= lst;
                }
            }
        }
        int ans = d - 1;
        for(pair<ll, int> f: fv) {
            ans = min(ans, d - (int) sts[f].size());
            if(f == bst) {
                break;
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}