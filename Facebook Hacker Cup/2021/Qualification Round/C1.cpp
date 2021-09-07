#include <bits/stdc++.h>

using namespace std;

int t, n, c[50], nxt[50], dp[50];
vector<int> g[50];

void dfs(int x, int p) {
    nxt[x] = -1;
    for(int i: g[x]) {
        if(i != p) {
            dfs(i, x);
            if(nxt[x] == -1 || dp[i] > dp[nxt[x]]) {
                nxt[x] = i;
                dp[x] = dp[i];
            }
        }
    }
    dp[x] += c[x];
}

int main() {
    freopen("gold_mine_chapter_1_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> c[i];
        }
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        dfs(0, 0);
        int ans = 0;
        for(int i: g[0]) {
            if(i != nxt[0]) {
                ans = max(ans, dp[i]);
            }
        }
        ans += dp[0];
        cout << "Case #" << _ << ": " << ans << endl;
        for(int i = 0; i < n; i++) {
            g[i].clear();
            dp[i] = 0;
        }
    }
}