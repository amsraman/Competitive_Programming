#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int tt, n, t[100000];
ll a[100000], dp[100000], sum[100000];
vector<int> g[100000];

void dfs(int x, int p) {
    dp[x] = sum[x] = 0;
    ll bst0 = 0;
    multiset<ll> lfs;
    for(int i: g[x]) {
        if(i != p) {
            dfs(i, x);
            dp[x] += dp[i];
            sum[x] += dp[i];
            bst0 = max(bst0, a[i]);
            lfs.insert(a[i] - dp[i] + sum[i]);
        }
    }
    for(int i: g[x]) {
        if(i != p && t[i] == 3) {
            lfs.erase(lfs.find(a[i] - dp[i] + sum[i]));
            if(!lfs.empty()) {
                bst0 = max(bst0, a[i] + *(--lfs.end()));
            }
            lfs.insert(a[i] - dp[i] + sum[i]);
        }
    }
    dp[x] += bst0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> tt;
    while(tt--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for(int i = 0; i < n; i++) {
            cin >> t[i];
        }
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        dfs(0, 0);
        cout << dp[0] + a[0] << '\n';
        for(int i = 0; i < n; i++) {
            g[i].clear();
        }
    }
}