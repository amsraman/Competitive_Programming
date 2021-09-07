#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int t, n;
string grid[50];
set<int> ok_rows;
map<int, int> num_ways;

int main() {
    freopen("xs_and_os_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> grid[i];
        }
        int ans = INF;
        for(int i = 0; i < n; i++) {
            int num_x = 0, num_dot = 0;
            for(int j = 0; j < n; j++) {
                num_x += (grid[i][j] == 'X');
                num_dot += (grid[i][j] == '.');
            }
            if(num_x + num_dot < n) {
                continue;
            }
            if(num_dot == 1) {
                ok_rows.insert(i);
            }
            ans = min(ans, num_dot);
            ++num_ways[num_dot];
        }
        for(int i = 0; i < n; i++) {
            int num_x = 0, num_dot = 0, rec_dot = 0;
            for(int j = 0; j < n; j++) {
                num_x += (grid[j][i] == 'X');
                num_dot += (grid[j][i] == '.');
                if(grid[j][i] == '.') {
                    rec_dot = j;
                }
            }
            if(num_x + num_dot < n) {
                continue;
            }
            ans = min(ans, num_dot);
            if(num_dot == 1 && ok_rows.count(rec_dot)) {
                --num_ways[1];
            }
            ++num_ways[num_dot];
        }
        cout << "Case #" << _ << ": ";
        if(ans == INF) {
            cout << "Impossible" << endl;
        } else {
            cout << ans << " " << num_ways[ans] << endl;
        }
        num_ways.clear();
        ok_rows.clear();
    }
}