#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

int n, m, a[1000][1000], dp[1000][1000][4], ans;
pair<int, int> dir[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector<pair<int, pair<int, int>>> ord;

bool ok(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
            ord.push_back({a[i][j], {i, j}});
        }
    }
    sort(ord.begin(), ord.end());
    for(pair<int, pair<int, int>> o: ord) {
        int x = o.s.f, y = o.s.s;
        bool term = true, start = true;
        for(pair<int, int> d: dir) {
            if(ok(x + d.f, y + d.s) && a[x + d.f][y + d.s] == a[x][y] - 1) {
                for(int j = 0; j < 3; j++) {
                    dp[x][y][j + 1] = (dp[x][y][j + 1] + dp[x + d.f][y + d.s][j]) % mod;
                }
                dp[x][y][3] = (dp[x][y][3] + dp[x + d.f][y + d.s][3]) % mod;
                start = false;
            }
            if(ok(x + d.f, y + d.s) && a[x + d.f][y + d.s] == a[x][y] + 1) {
                term = false;
            }
        }
        dp[x][y][0] = (int) start;
        if(term) {
            ans = (ans + dp[x][y][3]) % mod;
        }
    }
    cout << ans << '\n';
}
