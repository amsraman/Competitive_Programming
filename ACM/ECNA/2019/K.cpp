#include <bits/stdc++.h>

using namespace std;

int main() {
    string comp; cin >> comp;
    int n = (int) comp.length();
    vector<int> items(n), sz(5, 0), tot(5, 0);
    auto get_ind = [](char c) {
        if(c == 'A') return 0;
        if(c == 'E') return 1;
        if(c == 'I') return 2;
        if(c == 'O') return 3;
        return 4;
    };
    for(int i = 0; i < n; i++) {
        cin >> items[i];
    }
    int d; cin >> d;
    for(int i = 0; i < d; i++) {
        int del; cin >> del; --del;
        comp[del] = 'X'; items[del] = 0;
    }
    string want; cin >> want;
    for(char c: comp) {
        if(c == 'X') continue;
    }
    for(char c: want) {
        if(c == 'X') continue;
        ++sz[get_ind(c)];
    }
    vector<vector<int>> ps(n + 1, vector<int>(5, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 5; j++) {
            ps[i + 1][j] = ps[i][j];
        }
        if(comp[i] == 'X') continue;
        int ind = get_ind(comp[i]);
        ++sz[ind]; tot[ind] += items[i]; ps[i + 1][ind] += items[i];
    }
    auto cst = [&](int l, int r, int let) {
        return tot[let] - (ps[r + 1][let] - ps[l][let]);
    };
    vector<int> ord(5); iota(ord.begin(), ord.end(), 0);
    int ans = 1e9;
    do {
        vector<vector<int>> dp(n, vector<int>(5, 1e9));
        for(int i = 0; i < n; i++) {
            if(i >= sz[ord[0]] - 1) {
                dp[i][0] = cst(i - sz[ord[0]] + 1, i, ord[0]);
            }
            for(int j = 0; j < 5; j++) {
                if(i > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                if(j == 0) continue;
                int num_cells = sz[ord[j]];
                if(i >= num_cells) {
                    dp[i][j] = min(dp[i][j], dp[i - num_cells][j - 1] + cst(i - num_cells + 1, i, ord[j]));
                }
            }
        }
        ans = min(ans, dp[n - 1][4]);
    } while(next_permutation(ord.begin(), ord.end()));
    cout << ans << '\n';
}