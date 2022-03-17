#include <bits/stdc++.h>

using namespace std;

const int INF = 5000;

int n, m, k, dp[50][50][50][50][3], ep[51][50][3], ans = INF;
char grid[50][50];
string words[50];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    for(int i = 0; i < k; i++) {
        cin >> words[i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int w = 0; w < k; w++) {
                for(int l = 0; l < 50; l++) {
                    for(int d = 0; d < 3; d++) {
                        dp[i][j][w][l][d] = INF;
                    }
                }
            }
            for(int d = 0; d < 3; d++) {
                ep[i + 1][j][d] = INF;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int w = 0; w < k; w++) {
                for(int l = 0; l < words[w].length(); l++) {
                    if(grid[i][j] != words[w][l]) {
                        continue;
                    }
                    if(l == 0) {
                        dp[i][j][w][l][0] = min({ep[i][j][0], ep[i][j][1], ep[i][j][2]}) + 1;
                    } else if(i > 0) {
                        dp[i][j][w][l][0] = min({dp[i - 1][j][w][l - 1][0], dp[i - 1][j][w][l - 1][1], dp[i - 1][j][w][l - 1][2]}) + 1;
                    }
                }
                ep[i + 1][j][0] = min(ep[i + 1][j][0], dp[i][j][w][words[w].length() - 1][0]);
            }
        }
        for(int j = 1; j < m; j++) {
            for(int w = 0; w < k; w++) {
                for(int l = 0; l < words[w].length(); l++) {
                    if(grid[i][j] != words[w][l]) {
                        continue;
                    }
                    if(l == 0) {
                        dp[i][j][w][l][1] = min(ep[i + 1][j - 1][0], ep[i + 1][j - 1][1]) + 1;
                    } else {
                        dp[i][j][w][l][1] = min(dp[i][j - 1][w][l - 1][0], dp[i][j - 1][w][l - 1][1]) + 1;
                    }
                }
                ep[i + 1][j][1] = min(ep[i + 1][j][1], dp[i][j][w][words[w].length() - 1][1]);
            }
        }
        for(int j = m - 2; j >= 0; j--) {
            for(int w = 0; w < k; w++) {
                for(int l = 0; l < words[w].length(); l++) {
                    if(grid[i][j] != words[w][l]) {
                        continue;
                    }
                    if(l == 0) {
                        dp[i][j][w][l][2] = min(ep[i + 1][j + 1][0], ep[i + 1][j + 1][2]) + 1;
                    } else {
                        dp[i][j][w][l][2] = min(dp[i][j + 1][w][l - 1][0], dp[i][j + 1][w][l - 1][2]) + 1;
                    }
                }
                ep[i + 1][j][2] = min(ep[i + 1][j][2], dp[i][j][w][words[w].length() - 1][2]);
            }
        }
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < 3; j++) {
            ans = min(ans, ep[n][i][j]);
        }
    }
    if(ans == INF) {
        cout << "impossible\n";
    } else {
        cout << ans << '\n';
    }
}