#include <bits/stdc++.h>

using namespace std;

int n, k, a[200000], sz[200000], dp[200000], mx1[200000], mx2[200000], mx_dp;
vector<int> g[200000];

void dfs1(int x, int p = 0) {
    sz[x] = 1;
    for(int u: g[x]) {
        if(u != p) {
            dfs1(u,x);
            sz[x] += sz[u];
        }
    }
}

void dfs2(int x, int lim, int p = 0) {
    mx1[x] = mx2[x] = 0, dp[x] = 1;
    for(int u: g[x]) {
        if(u != p) {
            dfs2(u,lim,x);
            if(dp[u] == sz[u]) {
                dp[x] += dp[u];
            } else {
                if(dp[u] > mx2[x] && dp[u] <= mx1[x]) {
                    mx2[x] = dp[u];
                }
                mx1[x] = max(mx1[x],dp[u]);
            }
        }
    }
    dp[x] = (a[x] >= lim) * (dp[x] + mx1[x]);
}

void dfs3(int x, int down, int lim, int p = 0) {
    if(down == n-sz[x]) {
        dp[x] += down * (a[x] >= lim);
    } else {
        dp[x] += (max(down,mx1[x])-mx1[x]) * (a[x] >= lim);
        if(down >= mx1[x]) {
            mx2[x] = mx1[x], mx1[x] = down;
        } else if(down >= mx2[x]) {
            mx2[x] = down;
        }
    }
    mx_dp = max(mx_dp,dp[x]);
    for(int u: g[x]) {
        if(u != p) {
            if(dp[u] == sz[u]) {
                dfs3(u,dp[x] - dp[u] * (a[x] >= lim),lim,x);
            } else {
                dfs3(u,dp[x] + (dp[u] == mx1[x] ? mx2[x]-mx1[x] : 0) * (a[x] >= lim),lim,x);
            }
        }
    }
}

int main() {
    cin >> n >> k;
    for(int i = 0; i<n; i++) {
        cin >> a[i];
    }
    for(int i = 0, u, v; i<n-1; i++) {
        cin >> u >> v;
        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }
    dfs1(0);
    int lb = 0, ub = 1e6;
    while(lb<ub) {
        int mid = (lb+ub+1)/2;
        dfs2(0,mid);
        mx_dp = 0, dfs3(0,0,mid);
        if(mx_dp < k) {
            ub = mid-1;
        } else {
            lb = mid;
        }
    }
    cout << ub << endl;
}