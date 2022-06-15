#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 0xfffffffffffffff;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, s;
    cin >> n >> s;
    vector<int> a(n), pv(n), nxt(n), lst(n), sgn(n);
    vector<ll> dp(n, INF);
    map<int, vector<int>> groups;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        groups[a[i]].push_back(i);
    }
    groups[-2e9].push_back(s - 1);
    auto dist = [&](int x, int y) {
        if(x > y) {
            return n - x + y;
        }
        return y - x;
    };
    auto norm = [&](int x) {
        x = (abs(x + n) < abs(x) ? x + n : x);
        x = (abs(x - n) < abs(x) ? x - n : x);
        return x;
    };
    for(auto it = ++groups.begin(); it != groups.end(); it++) {
        vector<int> cur = it->s, prv = prev(it)->s;
        int sz = cur.size();
        bool st = prev(it)->f == -2e9;
        for(int i = 0; i < sz; i++) {
            pv[cur[i]] = cur[(i + sz - 1) % sz];
            nxt[cur[i]] = cur[(i + 1) % sz];
        }
        for(int c: cur) {
            for(int p: prv) {
                ll pd = (st ? 0 : dp[p]);
                if(c == p) {
                    dp[c] = n, lst[c] = p;
                }
                ll cw = pd + min(dist(p, pv[c]), dist(pv[c], p)) + dist(c, pv[c]);
                ll ccw = pd + min(dist(p, nxt[c]), dist(nxt[c], p)) + dist(nxt[c], c);
                if(cw < dp[c]) {
                    dp[c] = cw, lst[c] = p, sgn[c] = 1;
                }
                if(ccw < dp[c]) {
                    dp[c] = ccw, lst[c] = p, sgn[c] = -1;
                }
            }
        }
    }
    int mx = (--groups.end())->f, st = -1;
    for(int i = 0; i < n; i++) {
        if(a[i] == mx && (st == -1 || dp[i] < dp[st])) {
            st = i;
        }
    }
    cout << dp[st] << '\n';
    vector<int> ans;
    while(ans.size() < n) {
        vector<int> vec = groups[a[st]];
        int sg = sgn[st], sz = vec.size(), ind = 0;
        while(vec[ind] != st) {
            ++ind;
        }
        for(int i = 0; i + 1 < sz; i++) {
            int nxt_ind = (ind + sg + sz) % sz;
            ans.push_back(norm(vec[ind] - vec[nxt_ind]));
            ind = nxt_ind;
        }
        ans.push_back(norm(vec[ind] - lst[st]));
        st = lst[st];
    }
    reverse(ans.begin(), ans.end());
    for(int a: ans) {
        cout << (a >= 0 ? '+' : '-') << abs(a) << '\n';
    }
}