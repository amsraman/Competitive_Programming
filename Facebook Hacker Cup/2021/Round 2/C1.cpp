#include <bits/stdc++.h>

using namespace std;

int t, r, c, k, num[2000000];
string grid[2000000];

int main() {
    freopen("valet_parking_chapter_1_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> r >> c >> k;
        for(int i = 0; i < r; i++) {
            cin >> grid[i];
        }
        memset(num, 0, sizeof(num));
        for(int i = 0; i < c; i++) {
            int num_xs = 0;
            for(int j = 0; j < r; j++) {
                num_xs += (grid[j][i] == 'X');
                if(j >= k - 1) {
                    num[j - k + 1] += (grid[j][i] == 'X');
                    if(num_xs == k) {
                        for(int nxt = j - k + 2; nxt < r; nxt++) {
                            num[nxt] += 1;
                        }
                        break;
                    }
                }
            }
        }
        int ans = 1e9;
        for(int i = 0; i < r; i++) {
            ans = min(ans, num[i] + i);
        }
        memset(num, 0, sizeof(num));
        for(int i = 0; i < c; i++) {
            int num_xs = 0;
            for(int j = r - 1; j >= 0; j--) {
                num_xs += (grid[j][i] == 'X');
                if(j <= k - 1) {
                    num[k - 1 - j] += (grid[j][i] == 'X');
                    if(num_xs == r - k + 1) {
                        for(int nxt = k - j; nxt < r; nxt++) {
                            num[nxt] += 1;
                        }
                        break;
                    }
                }
            }
        }
        for(int i = 0; i < r; i++) {
            ans = min(ans, num[i] + i);
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}