#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> grid(n);
    vector<int> ans;
    vector<pair<int, int>> queries(k);
    vector<vector<int>> ps(n + 1, vector<int>(m + 1, 0)), up(n + 1, vector<int>(m, 0)), down(n + 1, vector<int>(m, 0));
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
        for(int j = 0; j < m; j++) {
            ps[i + 1][j + 1] = grid[i][j] == 'X';
        }
    }
    for(int i = 0; i < k; i++) {
        cin >> queries[i].f >> queries[i].s;
        ps[queries[i].f][queries[i].s] = 1;
        --queries[i].f, --queries[i].s;
        grid[queries[i].f][queries[i].s] = 'X';
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            ps[i][j] += ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
        }
    }
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            down[i + 1][j] = (grid[i][j] == '.' ? down[i][j] + 1 : 0);
        }
        for(int i = n - 1; i >= 0; i--) {
            up[i][j] = (grid[i][j] == '.' ? up[i + 1][j] + 1 : 0);
        }
    }
    int lb = 0, ub = min(n, m);
    while(lb < ub) {
        bool found = false;
        int mid = (lb + ub + 1) >> 1;
        for(int i = 0; i + mid <= n; i++) {
            for(int j = 0; j + mid <= m; j++) {
                if(ps[i + mid][j + mid] - ps[i + mid][j] - ps[i][j + mid] + ps[i][j] == 0) {
                    found = true;
                }
            }
        }
        if(found) {
            lb = mid;
        } else {
            ub = mid - 1;
        }
    }
    int cur = ub + 1;
    for(int i = k - 1; i >= 0; i--) {
        ans.push_back(cur - 1);
        int x = queries[i].f, y = queries[i].s;
        grid[x][y] = '.';
        up[x][y] = up[x + 1][y] + 1;
        down[x + 1][y] = down[x][y] + 1;
        for(int j = x - 1; j >= 0; j--) {
            if(grid[j][y] == 'X') {
                break;
            }
            up[j][y] += up[x][y];
        }
        for(int j = x + 1; j < n; j++) {
            if(grid[j][y] == 'X') {
                break;
            }
            down[j + 1][y] += down[x + 1][y];
        }
        vector<int> mn_up(m), mn_down(m);
        mn_up[y] =  up[x][y], mn_down[y] = down[x + 1][y];
        for(int j = y - 1; j >= 0; j--) {
            mn_up[j] = min(up[x][j], mn_up[j + 1]);
            mn_down[j] = min(down[x + 1][j], mn_down[j + 1]);
        }
        for(int j = y + 1; j < m; j++) {
            mn_up[j] = min(up[x][j], mn_up[j - 1]);
            mn_down[j] = min(down[x + 1][j], mn_down[j - 1]);
        }
        while(cur <= min(n, m)) {
            bool found = false;
            for(int j = 0; j <= y; j++) {
                if(j + cur > y && j + cur <= m) {
                    int tot_up = min(mn_up[j], mn_up[j + cur - 1]), tot_down = min(mn_down[j], mn_down[j + cur - 1]);
                    int sz = tot_up + tot_down - 1;
                    if(sz >= cur) {
                        found = true;
                    }
                }
            }
            if(!found) {
                break;
            }
            ++cur;
        }
    }
    reverse(ans.begin(), ans.end());
    for(int a: ans) {
        cout << a << '\n';
    }
}