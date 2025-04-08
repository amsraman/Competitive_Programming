#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; long long t; char op; cin >> n >> m >> t >> op;
    vector<pair<int, int>> sq;
    for(int i = 0; i < m; i++) {
        int r, c; cin >> r >> c; sq.emplace_back(r - 1, c - 1);
    }
    vector<bool> good(1 << m, true);
    for(int i = 0; i < 1 << m; i++) {
        vector<bool> visr(n, false), visc(n, false);
        for(int j = 0; j < m; j++) {
            if((i >> j) & 1) {
                auto [r, c] = sq[j];
                if(visr[r] || visc[c]) good[i] = false;
                visr[r] = visc[c] = true;
            }
        }
    }
    long long ans = 0;
    if(op == '+') {
        vector<vector<vector<int>>> dp(1 << m, vector<vector<int>>(t + 1, vector<int>(n + 1, 0))); dp[0][0][0] = 1;
        for(int num = 1; num <= n; num++) {
            for(int msk = 0; msk < 1 << m; msk++) {
                for(int sub_msk = msk;; sub_msk = (sub_msk - 1) & msk) {
                    int sz = __builtin_popcount(sub_msk);
                    if(good[sub_msk]) {
                        for(int sum = sz * num; sum <= t; sum++) {
                            dp[msk][sum][num] += dp[msk ^ sub_msk][sum - sz * num][num - 1];
                        }
                    }
                    if(sub_msk == 0) break;
                }
            }
        }
        ans = dp[(1 << m) - 1][t][n];
    } else if(op == '*') {
        vector<ll> divs;
        for(int i = 1; 1LL * i * i <= t; i++) {
            if(t % i == 0) {
                divs.push_back(i);
                if(i != t / i) divs.push_back(t / i);
            }
        }
        sort(divs.begin(), divs.end()); int div_sz = (int) divs.size();
        map<int, int> ind;
        for(int i = 0; i < div_sz; i++) {
            ind[divs[i]] = i;
        }
        vector<vector<vector<int>>> dp(1 << m, vector<vector<int>>(div_sz, vector<int>(n + 1, 0))); dp[0][0][0] = 1;
        for(int num = 1; num <= n; num++) {
            vector<ll> exp(m + 1, 1);
            for(int i = 1; i <= m; i++) exp[i] = exp[i - 1] * num;
            for(int msk = 0; msk < 1 << m; msk++) {
                for(int sub_msk = msk;; sub_msk = (sub_msk - 1) & msk) {
                    int sz = __builtin_popcount(sub_msk);
                    if(good[sub_msk]) {
                        for(int prod_ind = 0; prod_ind < div_sz; prod_ind++) {
                            ll prod = divs[prod_ind];
                            if(prod % exp[sz] == 0) {
                                dp[msk][prod_ind][num] += dp[msk ^ sub_msk][ind[prod / exp[sz]]][num - 1];
                            }
                        }
                    }
                    if(sub_msk == 0) break;
                }
            }
        }
        ans = dp[(1 << m) - 1][div_sz - 1][n];
    } else if(op == '-') {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(i == j && (sq[0].first == sq[1].first || sq[0].second == sq[1].second)) continue;
                if(i - j == t || j - i == t) {
                    ++ans;
                }
            }
        }
    } else {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(i == j && (sq[0].first == sq[1].first || sq[0].second == sq[1].second)) continue;
                if(i == t * j || j == t * i) {
                    ++ans;
                }
            }
        }
    }
    cout << ans << '\n';
}
/*
8 3 6 +
5 2 6 2 5 1
*/