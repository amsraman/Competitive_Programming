#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> f(n), taken(n, 0);
    set<int> rem;
    for(int i = 0; i < n; i++) {
        cin >> f[i]; rem.insert(i);
    }
    ll ans = 0;
    for(int i = 0, amt = 0; i < n + m - 1; i++) {
        int l = i - m + 1, r = i;
        while(amt < k && !rem.empty()) {
            int lst = *prev(rem.upper_bound(r));
            if(lst < l || lst > r) break;
            int take = min(k - amt, f[lst] - taken[lst]);
            ans += take, amt += take, taken[lst] += take;
            if(taken[lst] == f[lst]) rem.erase(lst);
        }
        if(l >= 0) amt -= taken[l];
    }
    cout << ans << '\n';
}