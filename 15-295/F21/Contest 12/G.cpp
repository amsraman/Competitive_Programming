#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n;
ll dp[200000][2], ans;
// 0: increasing as you go up
// 1: decreasing as you go up
vector<pair<int, int>> g[200000];

void dfs(int x, int p, int lb, int ub) {
    vector<pair<int, ll>> inc, dec;
    ll tot_dec = 0;
    dp[x][0] = dp[x][1] = 1;
    for(pair<int, int> e: g[x]) {
        if(e.f != p) {
            dfs(e.f, x, e.s, e.s);
            if(ub > e.s) {
                dp[x][0] += dp[e.f][0];
            }
            if(lb < e.s) {
                dp[x][1] += dp[e.f][1];
            }
            inc.push_back({e.s, dp[e.f][0]});
            dec.push_back({e.s, dp[e.f][1]});
            ans += dp[e.f][0] + dp[e.f][1];
        }
    }
    sort(inc.begin(), inc.end());
    sort(dec.begin(), dec.end());
    for(int i = inc.size() - 1, j = dec.size() - 1; i >= 0; i--) {
        while(j >= 0 && dec[j].f > inc[i].f) {
            tot_dec += dec[j--].s;
        }
        ans += inc[i].s * tot_dec;
    }
}

int main() {
    cin >> n;
    for(int i = 0, a, b, c; i < n - 1; i++) {
        cin >> a >> b >> c;
        g[a - 1].push_back({b - 1, c});
        g[b - 1].push_back({a - 1, c});
    }
    dfs(0, 0, -1, 2e9);
    cout << ans << endl;
}