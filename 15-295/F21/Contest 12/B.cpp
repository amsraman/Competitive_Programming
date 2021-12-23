#include <bits/stdc++.h>

using namespace std;

int n, dp[100000][4];
// 0 - root isn't an md but is monitored by a kid
// 1 - root is an md
// 2 - root isn't monitored and needs its parent
// 3 - root is monitored but still needs the parent
vector<int> g[100000];

void dfs(int x, int p) {
    dp[x][0] = ((x > 0 && g[x].size() == 1) ? n + 1 : 0), dp[x][1] = 1, dp[x][3] = n + 1;
    int tot = 0;
    multiset<int> difs;
    for(int i: g[x]) {
        if(i != p) {
            dfs(i, x);
            dp[x][0] += min(dp[i][0], dp[i][1]);
            dp[x][1] += min({dp[i][0], dp[i][1], dp[i][2], dp[i][3]});
            tot += min({dp[i][0], dp[i][1], dp[i][3]});
            difs.insert(min(dp[i][0], dp[i][1]) - min({dp[i][0], dp[i][1], dp[i][3]}));
        }
    }
    dp[x][2] = tot;
    for(int i: g[x]) {
        if(i != p) {
            dp[x][0] = min(dp[x][0], tot + min(dp[i][0], dp[i][1]) - min({dp[i][0], dp[i][1], dp[i][3]}));
            tot += dp[i][2] - min({dp[i][0], dp[i][1], dp[i][3]});
            difs.erase(difs.find(min(dp[i][0], dp[i][1]) - min({dp[i][0], dp[i][1], dp[i][3]})));
            dp[x][2] = min(dp[x][2], tot);
            if(!difs.empty()) {
                dp[x][3] = min(dp[x][3], tot + *difs.begin());
            }
            tot += min({dp[i][0], dp[i][1], dp[i][3]}) - dp[i][2];
            difs.insert(min(dp[i][0], dp[i][1]) - min({dp[i][0], dp[i][1], dp[i][3]}));
        }
    }
}

int main() {
    cin >> n;
    for(int i = 0, a, b; i < n - 1; i++) {
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    dfs(0, 0);
    cout << min({dp[0][0], dp[0][1], dp[0][3]}) << endl;
}