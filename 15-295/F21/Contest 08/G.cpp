#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int n, p[40], init_total, fact[81], inv[81], ncr[81][81];
array<int, 41> init;
map<tuple<array<int, 41>, int, int, int>, int> memo;
bool vis[40];

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret = mul(ret, x);
        }
        x = mul(x, x), y >>= 1;
    }
    return ret;
}

int dp(array<int, 41> cycles, int pv_moves, int cur_moves, int cur_len, int nodes_left) {
    if(pv_moves == 0) {
        return 0;
    }
    if(nodes_left == 0) {
        return 1;
    }
    if(memo.count({cycles, pv_moves, cur_moves, cur_len})) {
        return memo[{cycles, pv_moves, cur_moves, cur_len}];
    }
    int tot = 0, cur, per_cyc, tot_cycs = 1, nxt = cur_len + 1;
    while(nxt < n && cycles[nxt] == 0) {
        ++nxt;
    }
    if(pv_moves == -1) {
        per_cyc = exp(mul(fact[n], inv[nodes_left + cur_moves]), cur_len);
    } else {
        per_cyc = (exp(mul(fact[n], inv[nodes_left + cur_moves]), cur_len) - exp(mul(fact[n], inv[nodes_left + cur_moves + pv_moves]), cur_len) + mod) % mod;
    }
    // Case over the number of cycles with length cur_len
    for(int i = 0; i <= cycles[cur_len]; i++) {
        cycles[cur_len] -= i;
        if(cur_len == n) {
            cur = dp(cycles, cur_moves + i * cur_len, 0, 1, nodes_left - i * cur_len);
        } else {
            cur = dp(cycles, pv_moves, cur_moves + i * cur_len, nxt, nodes_left - i * cur_len);
        }
        cycles[cur_len] += i, tot = (tot + mul(ncr[cycles[cur_len]][i], mul(tot_cycs, cur))) % mod, tot_cycs = mul(tot_cycs, per_cyc);
    }
    return memo[{cycles, pv_moves, cur_moves, cur_len}] = tot;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }
    fact[0] = ncr[0][0] = 1;
    for(int i = 1; i <= 2 * n; i++) {
        ncr[i][0] = 1, fact[i] = mul(fact[i - 1], i), inv[i] = exp(i, mod - 2);
        for(int j = 1; j <= i; j++) {
            ncr[i][j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % mod;
        }
    }
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            int cur = p[i] - 1, cyc_len = 1;
            vis[cur] = true;
            while(cur != i) {
                cur = p[cur] - 1, ++cyc_len, vis[cur] = true;
            }
            ++init[cyc_len], ++init_total;
        }
    }
    cout << dp(init, -1, 0, 1, n) << '\n';
}