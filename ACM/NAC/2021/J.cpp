#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, k, cost[26][26], dp[51][26], ans;
string comb;

int main() {
    cin >> n >> k;
    memset(cost, -1, sizeof(cost));
    memset(dp, INF, sizeof(dp));
    for(int i = 0, c; i < n; i++) {
        cin >> comb >> c;
        cost[(comb[0] - 'a')][(comb[1] - 'a')] = c;
    }
    for(int i = 0; i < 26; i++) {
        dp[0][i] = 0;
    }
    for(int i = 1; i <= k / 2; i++) {
        for(int l1 = 0; l1 < 26; l1++) {
            for(int l2 = 0; l2 < 26; l2++) {
                if(min(cost[l1][l2], cost[l2][l1]) > -1) {
                    dp[i][l2] = min(dp[i][l2], dp[i - 1][l1] + cost[l1][l2] + cost[l2][l1]);
                }
            }
        }
    }
    ans = INF;
    for(int i = 0; i < 26; i++) {
        if(k & 1) {
            ans = min(ans, dp[k / 2][i]);
        } else if(cost[i][i] != -1) {
            ans = min(ans, dp[k / 2 - 1][i] + cost[i][i]);
        }
    }
    cout << (ans == INF ? -1 : ans) << endl;
}