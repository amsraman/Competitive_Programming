#include <bits/stdc++.h>

using namespace std;

int n, m, q, ps[1000001];
string grid[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    for(int i = 0; i < m - 1; i++) {
        for(int j = 1; j < n; j++) {
            if(grid[j][i] == 'X' && grid[j - 1][i + 1] == 'X') {
                ++ps[i + 1];
            }
        }
    }
    for(int i = 1; i <= m; i++) {
        ps[i] += ps[i - 1];
    }
    cin >> q;
    while(q--) {
        int x, y;
        cin >> x >> y;
        cout << (ps[y - 1] - ps[x - 1] == 0 ? "YES" : "NO") << '\n';
    }
}