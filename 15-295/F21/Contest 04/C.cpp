#include <bits/stdc++.h>

using namespace std;

int n, dp[100000], ans;
bool nd[100000];
vector<int> g[100000];

void dfs(int x, int p) {
    dp[x] = 1;
    for(int i: g[x]) {
        if(i != p) {
            dfs(i, x);
            if(nd[i]) {
                dp[x] += dp[i];
            }
        }
    }
    if(dp[x] % 2 == 1) {
        nd[x] = true;
    } else {
        ++ans;
    }
}

int main() {
    cin >> n;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs(0, 0);
    cout << (nd[0] ? -1 : ans - 1) << endl;
}