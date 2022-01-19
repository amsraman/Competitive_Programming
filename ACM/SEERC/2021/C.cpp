#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int n, c[3000], num[3000], sz[3000], val[3000], dp[3000][6001], contrib[6001], mn[3000], mx[3000], ans;
vector<int> g[3000];

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

void init(int x, int p) {
    sz[x] = 1;
    for(int i: g[x]) {
        if(i != p) {
            init(i, x);
            sz[x] += sz[i];
        }
    }
}

void dfs(int x, int p, int nm) {
    val[x] = (c[x] == nm ? 1 : -1);
    mn[x] = -1, mx[x] = 1;
    dp[x][3000 + val[x]] = 1;
    int num_c = num[nm], so_far = 1;
    for(int i: g[x]) {
        if(i != p) {
            dfs(i, x, nm);
            for(int j = mn[i]; j <= mx[i]; j++) {
                if(dp[i][3000 + j] == 0) {
                    continue;
                }
                for(int k = mn[x]; k <= mx[x]; k++) {
                    if(k + j >= -min(so_far + sz[i], num_c) && k + j <= min(so_far + sz[i], num_c)) {
                        contrib[3000 + k + j] = (contrib[3000 + k + j] + mul(dp[i][3000 + j], dp[x][3000 + k])) % mod;
                    }
                }
            }
            so_far += sz[i];
            for(int j = -min(so_far, num_c); j <= min(so_far, num_c); j++) {
                dp[x][3000 + j] = (dp[x][3000 + j] + contrib[3000 + j]) % mod;
                if(contrib[3000 + j] != 0) {
                    mn[x] = min(mn[x], j), mx[x] = max(mx[x], j);
                }
                contrib[3000 + j] = 0;
            }
        }
    }
    for(int i = 1; i <= num_c; i++) {
        ans = (ans + dp[x][3000 + i]) % mod;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> c[i];
        --c[i], ++num[c[i]];
    }
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    init(0, 0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = -num[i]; k <= num[i]; k++) {
                dp[j][3000 + k] = 0;
            }
        }
        dfs(0, 0, i);
    }
    cout << ans << '\n';
}