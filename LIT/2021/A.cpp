#include <bits/stdc++.h>

using namespace std;

int n, m, k, grid[100][100], best[100][100], ans;

int main() {
    cin >> n >> m >> k;
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++) {
            cin >> grid[i][j];
        }
    }
    vector<int> streaks;
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++) {
            best[i][j] = grid[i][j] * (j == 0 ? 1 : best[i][j-1] + 1);
            if(grid[i][j] == 1) {
                if(j == m-1 || grid[i][j+1] == 0) {
                    streaks.push_back(best[i][j]);
                }
            }
        }
    }
    sort(streaks.begin(),streaks.end());
    reverse(streaks.begin(),streaks.end());
    for(int i = 0; i<k; i++) {
        ans += streaks[i];
    }
    cout << ans << endl;
}
