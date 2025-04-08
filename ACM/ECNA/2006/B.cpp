#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    for(int _ = 1; n > 0; _++) {
        vector<vector<int>> dist(n + 1, vector<int>(n + 1));
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                cin >> dist[i][j];
            }
        }
        for(int k = 0; k < n + 1; k++) {
            for(int i = 0; i < n + 1; i++) {
                for(int j = 0; j < n + 1; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 0);
        int ans = 1e9;
        do {
            int res = dist[0][perm[0] + 1] + dist[perm[n - 1] + 1][0];
            for(int i = 0; i < n - 1; i++) {
                res += dist[perm[i] + 1][perm[i + 1] + 1];
            }
            ans = min(ans, res);
        } while(next_permutation(perm.begin(), perm.end()));
        cout << ans << '\n';
        cin >> n;
    }
}