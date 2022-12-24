#include <bits/stdc++.h>

using namespace std;

int n, m, k, ans[2000];
string grid[2000];

int main() {
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 'R' && i + j < m) {
                ++ans[j + i];
            } else if(grid[i][j] == 'L' && j - i >= 0) {
                ++ans[j - i];
            } else if(grid[i][j] == 'U' && i % 2 == 0) {
                ++ans[j];
            }
        }
    }
    for(int i = 0; i < m; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}