#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 1e9 + 7;

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> nxt(n), cyc(n, -1), in_deg(n, 0);
    vector<vector<int>> g(n);
    for(int i = 0; i < n; i++) {
        cin >> nxt[i]; --nxt[i];
    }
    for(int i = 0; i < n; i++) {
        int p1 = i, p2 = i;
        bool bad = false;
        do {
            if(cyc[p1] != -1) {
                bad = true;
                break;
            }
            cyc[p1] = p1;
            p1 = nxt[p1], p2 = nxt[nxt[p2]];
        } while(p1 != p2);
        if(bad) continue;
        do {
            cyc[p2] = p1, p2 = nxt[p2];
        } while(p1 != p2);
    }
    for(int i = 0; i < n; i++) {
        if(cyc[i] == i && cyc[nxt[i]] != i) {
            g[cyc[nxt[i]]].push_back(i), ++in_deg[i];
        }
    }
    auto dfs = [&](auto rec, int u) -> int {
        int res = 1;
        for(int v: g[u]) {
            res = mul(res, rec(rec, v));
        }
        return (res + 1) % mod;
    };
    int ans = 1;
    for(int i = 0; i < n; i++) {
        if(in_deg[i] == 0 && i == cyc[i]) {
            ans = mul(ans, dfs(dfs, i));
        }
    }
    cout << (ans + mod - 1) % mod << '\n';
}