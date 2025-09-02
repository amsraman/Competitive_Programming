#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<bool> used(1 << 22, false), vis(1 << 22, false);
    queue<int> q; vis[0] = true;
    for(int val: a) {
        int msb = 31 - __builtin_clz(val), lw = (1 << msb) - 1, bel = val ^ lw;
        if(!used[bel]) {
            q.push(bel); used[bel] = true;
        }
        while(!q.empty()) {
            int msk = q.front(); q.pop();
            if(vis[msk ^ (1 << msb)]) vis[msk] = true;
            for(int i = 0; i < msb; i++) {
                if((msk >> i) & 1 ^ 1) continue;
                if(!used[msk ^ (1 << i)]) {
                    q.push(msk ^ (1 << i));
                    used[msk ^ (1 << i)] = true;
                }
            }
        }
    }
    int res = 0;
    for(int msk = 0; msk < 1 << 22; msk++) {
        if(!vis[msk]) continue;
        res = max(res, __builtin_popcount(msk));
    }
    cout << res << '\n';
}
/*
f[msk] = is msk feasible?

this is true if there is a number such that its highest is msk's highest
- that number has zeros at the rest of msk
- and good[rest of msk]
*/