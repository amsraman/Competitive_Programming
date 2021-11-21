#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 1e9;

int n, m, msk[(1 << 18)], num[18];
ll bal[18], dp[19][(1 << 18)][19];
vector<int> dag[18], ord;
bool use[19][(1 << 18)][19];

void dfs(int x) {
    msk[x] = (1 << x);
    for(int i: dag[x]) {
        if(msk[i] == 0) {
            dfs(i);
        }
        msk[x] |= msk[i];
    }
    ord.push_back(x);
}

int main() {
    cin >> n >> m;
    for(int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        dag[u - 1].push_back(v - 1);
        bal[u - 1] += w, bal[v - 1] -= w;
    }
    for(int i = 0; i < n; i++) {
        if(msk[i] == 0) {
            dfs(i);
        }
    }
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < (1 << n); j++) {
            for(int k = 0; k <= n; k++) {
                dp[i][j][k] = INF;
            }
        }
    }
    reverse(ord.begin(), ord.end());
    dp[0][0][0] = 0;
    for(int i = 0; i <= n; i++) {
        if(i > 0) {
            for(int j = 0; j < (1 << n); j++) {
                dp[i][j][0] = dp[i - 1][j][n];
            }
        }
        for(int j = 0; j < (1 << n); j++) {
            for(int k = 0; k < n; k++) {
                dp[i][j][k + 1] = dp[i][j][k];
                if((msk[ord[k]] & j) == msk[ord[k]]) {
                    ll nxt = dp[i][j ^ (1 << ord[k])][k] + bal[ord[k]] * i;
                    if(nxt < dp[i][j][k + 1]) {
                        dp[i][j][k + 1] = nxt;
                        use[i][j][k + 1] = true;
                    }
                }
            }
        }
    }
    int cur_msk = (1 << n) - 1;
    for(int i = n; i >= 0; i--) {
        for(int j = n; j > 0; j--) {
            if(use[i][cur_msk][j]) {
                num[ord[j - 1]] = i;
                cur_msk ^= (1 << (ord[j - 1]));
            }
        }
    }
    for(int i = 0; i < n; i++) {
        cout << num[i] << " ";
    }
    cout << endl;
}