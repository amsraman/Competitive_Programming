#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n, a[100000], nxt[100000], pv[100000];

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        set<pair<int, int>> bp;
        for(int i = 0; i < n; i++) {
            nxt[i] = (i + 1) % n;
            pv[nxt[i]] = i;
            if(__gcd(a[i], a[nxt[i]]) == 1) {
                bp.insert({i, nxt[i]});
            }
        }
        int cur = 0;
        vector<int> ans;
        while(!bp.empty()) {
            auto it = bp.lower_bound({cur, -1});
            if(it == bp.end()) {
                it = bp.begin();
            }
            pair<int, int> np = *it;
            assert(bp.count(np));
            bp.erase(np);
            if(bp.count({np.s, nxt[np.s]})) {
                bp.erase(bp.find({np.s, nxt[np.s]}));
            }
            if(__gcd(a[np.f], a[nxt[np.s]]) == 1 && np.f != np.s) {
                bp.insert({np.f, nxt[np.s]});
            }
            ans.push_back(np.s);
            pv[nxt[np.s]] = pv[np.s];
            nxt[pv[np.s]] = nxt[np.s];
            cur = np.s + 1;
        }
        cout << ans.size() << " ";
        for(int i: ans) {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
}