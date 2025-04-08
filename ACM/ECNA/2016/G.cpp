#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    vector<vector<int>> init(3);
    int n = 0;
    for(int i = 0; i < 3; i++) {
        int m; cin >> m; init[i].resize(m); n += m;
        for(int j = 0; j < m; j++) {
            cin >> init[i][j]; --init[i][j];
        }
    }
    vector<ll> p2(n + 1); p2[0] = 1;
    for(int i = 1; i <= n; i++) {
        p2[i] = 2 * p2[i - 1];
    }
    vector<int> pos(n);
    for(int i = 0; i < 3; i++) {
        for(int j: init[i]) pos[j] = i;
    }
    auto solve = [&](auto rec, int x, int p) -> ll {
        if(x == -1) return 0;
        if(pos[x] == p) return rec(rec, x - 1, p);
        return rec(rec, x - 1, p ^ pos[x] ^ 3) + p2[x];
    };
    ll mv1 = solve(solve, n - 1, 2), mv2 = solve(solve, n - 1, 0);
    if(mv1 + mv2 == p2[n] - 1) {
        cout << mv1 << '\n';
    } else {
        cout << "No\n";
    }
}