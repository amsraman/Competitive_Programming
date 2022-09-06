#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, lp, xr, a[100000], par[100000], tot[2];
ll ans;
vector<int> g[100000];
map<int, int> cnt;

void dfs(int x, int p) {
    par[x] = p, ++tot[p];
    for(int u: g[x]) {
        dfs(u, p ^ 1);
    }
    if(g[x].empty()) {
        lp = p;
    }
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 1, p; i < n; i++) {
        cin >> p;
        g[p - 1].push_back(i);
    }
    dfs(0, 0);
    for(int i = 0; i < n; i++) {
        if(par[i] ^ lp) {
            ++cnt[a[i]];
        } else {
            xr ^= a[i];
        }
    }
    for(int i = 0; i < n; i++) {
        if(par[i] ^ lp ^ 1) {
            ans += cnt[xr ^ a[i]];
        }
    }
    if(xr == 0) {
        ans += 1LL * tot[0] * (tot[0] - 1) / 2 + 1LL * tot[1] * (tot[1] - 1) / 2;
    }
    cout << ans << endl;
}