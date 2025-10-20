#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int main() {
    ifstream cin("substitution_cipher_input.txt");
    ofstream cout("out.txt");
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        string e; int k; cin >> e >> k; --k;
        int n = (int) e.length();
        vector<bool> can_pair(n, false), can_prefix(n + 1, false), can_suffix(n + 1, false);
        auto is_dig = [&](int ind, int dig) {
            return e[ind] == '?' || e[ind] == char('0' + dig);
        };
        for(int i = 0; i < n - 1; i++) {
            for(int j = 1; j <= 26; j++) {
                if(e[i] != '0' && is_dig(i, j / 10) && is_dig(i + 1, j % 10)) {
                    can_pair[i] = true;
                }
            }
        }
        can_prefix[0] = can_suffix[n] = true;
        for(int i = 0; i < n; i++) {
            if(e[i] != '0' && can_prefix[i]) {
                can_prefix[i + 1] = true;
            }
            if(i > 0 && can_pair[i - 1] && can_prefix[i - 1]) {
                can_prefix[i + 1] = true;
            }
        }
        for(int i = n - 1; i >= 0; i--) {
            if(e[i] != '0' && can_suffix[i + 1]) {
                can_suffix[i] = true;
            }
            if(i < n - 1 && can_pair[i] && can_suffix[i + 2]) {
                can_suffix[i] = true;
            }
        }
        vector<bool> can_single(n, false), can_double(n, false);
        for(int i = 0; i < n; i++) {
            if(can_prefix[i] && can_suffix[i + 1] && e[i] != '0') {
                can_single[i] = true;
            }
            if(i < n - 1 && can_prefix[i] && can_suffix[i + 2] && can_pair[i]) {
                can_double[i] = true;
            }
        }
        vector<vector<int>> back_dp(n, vector<int>(10, 0));
        for(int i = 0; i < 10; i++) {
            if(i == 0 && can_single[n - 1]) continue;
            if(e[n - 1] == '?' || e[n - 1] == char('0' + i)) {
                back_dp[n - 1][i] = 1;
            }
        }
        for(int i = n - 2; i >= 0; i--) {
            for(int cur_dig = 0; cur_dig < 10; cur_dig++) {
                if(e[i] != '?' && e[i] != char('0' + cur_dig)) continue;
                if(can_single[i] && cur_dig == 0) continue;
                for(int nxt_dig = 0; nxt_dig < 10; nxt_dig++) {
                    int num = 10 * cur_dig + nxt_dig;
                    if(can_double[i] && (num == 0 || num > 26)) continue;
                    back_dp[i][cur_dig] = min(k + 1, back_dp[i][cur_dig] + back_dp[i + 1][nxt_dig]);
                }
            }
        }
        string res = e; int cur = k;
        for(int i = 0; i < n; i++) {
            if(res[i] != '?') continue;
            for(int dig = 9; dig >= 0; dig--) {
                if(i > 0 && can_double[i - 1]) {
                    int num = 10 * (res[i - 1] - '0') + dig;
                    if(num > 26) continue;
                }
                if(cur < back_dp[i][dig]) {
                    res[i] = char('0' + dig);
                    break;
                }
                cur -= back_dp[i][dig];
            }
        }
        for(int i = 0; i < n; i++) {
            if(e[i] == '?') {
                e[i] = '1';
            }
        }
        vector<int> front_dp(n + 1, 0); front_dp[0] = 1;
        for(int i = 0; i < n; i++) {
            if(e[i] != '0') {
                front_dp[i + 1] = (front_dp[i + 1] + front_dp[i]) % mod;
            }
            if(i > 0) {
                int two_back = 10 * (e[i - 1] - '0') + (e[i] - '0');
                if(e[i - 1] != '0' && two_back >= 1 && two_back <= 26) {
                    front_dp[i + 1] = (front_dp[i + 1] + front_dp[i - 1]) % mod;
                }
            }
        }
        cout << "Case #" << _ << ": " << res << " " << front_dp[n] << '\n';
    }
}