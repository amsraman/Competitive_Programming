#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

int t, k, dp[800000];
string u;

int mul(int a, int b) {
    return ((ll) a * b) % mod;
}

int main() {
    freopen("weak_typing_chapter_3_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> k >> u;
        int ans = 0;
        int len = 1, bal = 0, tot_bal = 0;
        vector<pair<int, char>> not_fs;
        if(u[0] == 'O' || u[0] == 'X') {
            not_fs.push_back({0, u[0]});
        }
        for(int i = 1; i < k; i++) {
            dp[i] = dp[i - 1];
            if(u[i] == '.') {
                ans = (mul(2, ans) + ((mul(len, dp[i]) + mul(len, tot_bal)) % mod)) % mod;
                if(!not_fs.empty() && (not_fs[0].s != not_fs.back().s)) {
                    ans = (ans + mul((len - not_fs[0].f + mod) % mod, not_fs.back().f + 1)) % mod;
                }
                dp[i] = (mul(dp[i], 2) + mul(len, bal)) % mod;
                tot_bal = (mul(tot_bal, 2) + mul(len, bal)) % mod;
                if(!not_fs.empty() && not_fs[0].s != not_fs.back().s) {
                    dp[i] = (dp[i] + not_fs.back().f + 1) % mod;
                    tot_bal = (tot_bal + ((len - not_fs[0].f + mod) % mod)) % mod;
                }
                bal = (mul(bal, 2) + (!not_fs.empty() && (not_fs[0].s != not_fs.back().s))) % mod;
                if(!not_fs.empty()) {
                    not_fs.push_back({(not_fs.back().f + len) % mod, not_fs.back().s});
                }
                len = mul(len, 2);
            } else if(u[i] == 'O' || u[i] == 'X') {
                if(!not_fs.empty() && not_fs.back().s != u[i]) {
                    dp[i] = (dp[i] + not_fs.back().f + 1) % mod;
                    bal = (bal + 1) % mod;
                }
                not_fs.push_back({len, u[i]});
                len = (len + 1) % mod;
                tot_bal = (tot_bal + bal) % mod;
                ans = (ans + dp[i]) % mod;
            } else {
                len = (len + 1) % mod;
                tot_bal = (tot_bal + bal) % mod;
                ans = (ans + dp[i]) % mod;
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}