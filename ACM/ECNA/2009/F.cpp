#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<vector<int>> factors(65537);
    for(int i = 1; i <= 65536; i++) {
        for(int j = i; j <= 65536; j += i) {
            factors[j].push_back(i);
        }
    }
    int r, c; cin >> r >> c;
    while(r > 0) {
        vector<vector<int>> a(r, vector<int>(c));
        int g = 0;
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                cin >> a[i][j];
                g = __gcd(g, a[i][j]);
            }
        }
        int ans = 0;
        for(int dx: factors[r]) {
            for(int dy: factors[c]) {
                if(dx == 1 && dy == 1) continue;
                if(dx == r && dy == c) continue;
                bool ok = true;
                for(int x = 0; x < r; x += dx) {
                    for(int y = 0; y < c; y += dy) {
                        for(int i = 0; i < dx; i++) {
                            for(int j = 0; j < dy; j++) {
                                if(1LL * a[x + i][y + j] * a[0][0] != 1LL * a[x][y] * a[i][j]) {
                                    ok = false;
                                }
                            }
                        }
                    }
                }
                ans += (int) ok;
            }
        }
        cout << ans * factors[g].size() << '\n';
        cin >> r >> c;
    }
}