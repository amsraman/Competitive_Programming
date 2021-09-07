#include <bits/stdc++.h>

using namespace std;

int n, grid[1024][1024], num[(1 << 20)], zer, ans;

int main() {
    cin >> n;
    for(int i = 0; i < (1 << n); i++) {
        for(int j = 0; j < (1 << n); j++) {
            cin >> grid[i][j];
            zer += (grid[i][j] == 0);
        }
    }
    for(int i = 0; i < (1 << n) - 1; i++) {
        for(int j = 0; j < (1 << n) - 1; j++) {
            int h = (grid[i][j] == grid[i][j + 1]) + (grid[i + 1][j] == grid[i + 1][j + 1]);
            int v = (grid[i][j] == grid[i + 1][j]) + (grid[i][j + 1] == grid[i + 1][j + 1]);
            if(h == 1 & v == 1) {
                if(grid[i + 1][j] == grid[i + 1][j + 1] && grid[i][j + 1] == grid[i + 1][j + 1]) {
                    ++num[grid[i + 1][j + 1]];
                } else {
                    ++num[grid[i][j]];
                }
            }
        }
    }
    ans = (zer == 1);
    for(int i = 1; i <= ((1 << (2 * n)) - 1) / 3; i++) {
        ans &= (num[i] == 1);
    }
    cout << ans << endl;
}