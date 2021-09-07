#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, k, problems[50];
ll dp[51][50][50], ans;

int main() {
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> problems[i];
    }
    sort(problems, problems + n);
    for(int i = 0; i < n; i++) {
        for(int len = 2; len <= min(i, k - 1); len++) {
            for(int pos1 = 0; pos1 < i - 1; pos1++) {
                for(int pos2 = pos1 + 1; pos2 < i; pos2++) {
                    if(problems[pos1] + problems[pos2] >= problems[i]) {
                        dp[len + 1][pos2][i] += dp[len][pos1][pos2];
                    }
                }
            }
        }
        for(int pos = 0; pos < i; pos++) {
            dp[2][pos][i] = 1;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            ans += dp[k][i][j];
        }
    }
    cout << ans << endl;
}