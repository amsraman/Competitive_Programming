#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 2e14;

int t, n, k, c[1000];
int tc;
ll dp[1000][1000][4], tmp[1000][4];
// dp[subtree][number of chains][configuration]
// config 0: root is not included at all
// config 1: root is included in a single-branch chain
// config 2: root is included in *at least* one dual-branch chain
vector<int> g[50];

void dfs(int v, int p) {
    for(int i = 0; i <= k; i++) {
        dp[v][i][0] = dp[v][i][1] = dp[v][i][2] = dp[v][i][3] = -INF;
    }
    dp[v][0][0] = 0;
    for(int i: g[v]) {
        if(i != p) {
            dfs(i, v);
            for(int x = 0; x < n; x++) {
                for(int y = 0; y < 4; y++) {
                    tmp[x][y] = dp[v][x][y];
                }
            }
            for(int x = 0; x < n; x++) {
                for(int y = 0; y < n; y++) {
                    if(x + y >= n) {
                        continue;
                    }
                    tmp[x + y][0] = max(tmp[x + y][0], dp[v][x][0] + max({dp[i][y][0], dp[i][y][1], dp[i][y][2], dp[i][y][3]}));
                    tmp[x + y][1] = max(tmp[x + y][1], dp[v][x][0] + max({dp[i][y][1], dp[i][y][3]}) + c[v]);
                    tmp[x + y][1] = max(tmp[x + y][1], dp[v][x][1] + max({dp[i][y][0], dp[i][y][1], dp[i][y][2], dp[i][y][3]}));
                    if(x + y > 0) {
                        tmp[x + y - 1][2] = max(tmp[x + y - 1][2], max(dp[v][x][1], dp[v][x][3]) + max(dp[i][y][1], dp[i][y][3]));
                    }
                    tmp[x + y][2] = max(tmp[x + y][2], dp[v][x][2] + max({dp[i][y][0], dp[i][y][1], dp[i][y][2], dp[i][y][3]}));
                    tmp[x + y][3] = max(tmp[x + y][3], dp[v][x][2] + max({dp[i][y][1], dp[i][y][3]}));
                    tmp[x + y][3] = max(tmp[x + y][3], dp[v][x][3] + max({dp[i][y][0], dp[i][y][1], dp[i][y][2], dp[i][y][3]}));
                }
            }
            for(int x = 0; x < n; x++) {
                for(int y = 0; y < 4; y++) {
                    dp[v][x][y] = tmp[x][y];
                }
            }
        }
    }
    for(int i = n - 1; i > 0; i--) {
        dp[v][i][1] = max(dp[v][i][1], dp[v][i - 1][0] + c[v]);
        dp[v][i][3] = max(dp[v][i][3], dp[v][i - 1][2]);
    }
}

int main() {
    freopen("gold_mine_chapter_2_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> k;
        tc = _;
        for(int i = 0; i < n; i++) {
            cin >> c[i];
        }
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        cout << "Case #" << _ << ": ";
        if(k == 0 || n == 1) {
            cout << c[0] << endl;
            for(int i = 0; i < n; i++) {
                g[i].clear();
            }
            continue;
        }
        dfs(0, 0);
        k = min(k, n - 1);
        for(int i = 0; i < n; i++) {
            for(int j = 1; j <= k; j++) {
                for(int pos = 0; pos < 4; pos++) {
                    dp[i][j][pos] = max(dp[i][j][pos], dp[i][j - 1][pos]);
                }
            }
        }
        cout << max({dp[0][k - 1][0], dp[0][k][1], dp[0][k][2], dp[0][k][3]}) << endl;
        for(int i = 0; i < n; i++) {
            g[i].clear();
        }
    }
}