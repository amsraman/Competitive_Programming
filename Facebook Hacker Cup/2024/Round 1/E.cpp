#include <bits/stdc++.h>
typedef __int128_t i128;

using namespace std;

const int mod = 998244353;

int main() {
    ifstream cin("wildcard_submissions_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<string> s(n); vector<int> sz(n);
        for(int i = 0; i < n; i++) {
            cin >> s[i]; sz[i] = (int) s[i].length();
        }
        vector<int> pw(101, 1);
        for(int i = 1; i <= 100; i++) {
            pw[i] = (26LL * pw[i - 1]) % mod;
        }
        vector<short> lcp(1 << n); vector<i128> ques(1 << n, 0);
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int pt = 0;
                while(pt < sz[i] && pt < sz[j] && (s[i][pt] == '?' || s[j][pt] == '?' || s[i][pt] == s[j][pt])) {
                    ++pt;
                }
                lcp[(1 << i) ^ (1 << j)] = pt;
            }
            for(int j = 0; j < sz[i]; j++) {
                if(s[i][j] == '?') {
                    ques[1 << i] ^= ((i128) 1) << j;
                }
            }
            lcp[1 << i] = sz[i];
        }
        for(int msk = 1; msk < 1 << n; msk++) {
            int len = __builtin_popcount(msk);
            int highest_bit = (1 << (31 - __builtin_clz(msk))), lowest_bit = msk & -msk;
            if(len > 1) {
                ques[msk] = ques[msk ^ lowest_bit] & ques[lowest_bit];
            }
            if(len <= 2) continue;
            lcp[msk] = min({lcp[msk ^ lowest_bit], lcp[msk ^ highest_bit], lcp[lowest_bit ^ highest_bit]});
        }
        vector<int> msk_val(1 << 16, 0);
        for(int msk = 0; msk < 1 << 16; msk++) {
            int num = 0;
            for(int bt = 0; bt < 16; bt++) {
                if((msk >> bt) & 1) ++num;
                msk_val[msk] = (msk_val[msk] + pw[num]) % mod;
            }
        }
        auto get_window = [&](i128 msk, int lo, int hi) -> int {
            int len = hi - lo + 1;
            return (msk >> lo) & ((1 << len) - 1);
        };
        int res = 1;
        for(int msk = 1; msk < 1 << n; msk++) {
            int len = __builtin_popcount(msk), ways = 0, num = 0;
            for(int i = 0; i < lcp[msk]; i += 16) {
                int cur = get_window(ques[msk], i, min(lcp[msk] - 1, i + 15));
                ways = (ways + 1LL * pw[num] * msk_val[cur]) % mod;
                int cut_off = max(0, i + 15 - (lcp[msk] - 1));
                cut_off = (1LL * cut_off * pw[num + __builtin_popcount(cur)]) % mod;
                ways = (ways - cut_off + mod) % mod;
                num += __builtin_popcount(cur);
            }
            if(len & 1) {
                res = (res + ways) % mod;
            } else {
                res = (res - ways + mod) % mod;
            }
        }
        cout << "Case #" << _ << ": " << res << endl;
    }
}