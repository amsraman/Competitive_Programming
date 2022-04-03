#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, f[100000], mx[100000];
ll ans;
vector<int> g[100000];

void dfs(int x) {
    mx[x] = f[x];
    vector<int> mxs;
    for(int u: g[x]) {
        dfs(u);
        mxs.push_back(mx[u]);
    }
    if(g[x].empty()) {
        return;
    }
    sort(mxs.begin(), mxs.end());
    mx[x] = max(mx[x], mxs[0]);
    for(int i = 1; i < mxs.size(); i++) {
        ans += mxs[i];
    }
}

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> f[i];
        }
        vector<bool> abyss(n, false);
        for(int i = 0, p; i < n; i++) {
            cin >> p;
            if(p != 0) {
                g[p - 1].push_back(i);
            } else {
                abyss[i] = true;
            }
        }
        ans = 0;
        for(int i = 0; i < n; i++) {
            if(abyss[i]) {
                dfs(i);
                ans += mx[i];
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
        for(int i = 0; i < n; i++) {
            g[i].clear();
        }
    }
}