#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<string> grid(n);
    int sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
        for(int j = 0; j < m; j++) {
            sum += grid[i][j] - '0';
        }
    }
    cout << (sum / 2 >= k ? "YES" : "NO") << '\n';
}