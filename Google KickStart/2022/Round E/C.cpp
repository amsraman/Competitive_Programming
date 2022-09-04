#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mod1 = 1e9 + 7, mod2 = 998244353, mod3 = 1e8 + 7;

int pw[100001][2];
pair<int, int> hsh[100001][2];

pair<int, int> get_hsh(int ind, int lo, int hi) {
    int pf1 = (1LL * hsh[lo][ind].f * pw[hi - lo + 1][0]) % mod2;
    int pf2 = (1LL * hsh[lo][ind].s * pw[hi - lo + 1][1]) % mod1;
    int hsh1 = (hsh[hi + 1][ind].f - pf1 + mod2) % mod2;
    int hsh2 = (hsh[hi + 1][ind].s - pf2 + mod1) % mod1;
    return {hsh1, hsh2};
}

int main() {
    pw[0][0] = pw[0][1] = 1;
    for(int i = 1; i <= 1e5; i++) {
        pw[i][0] = (1LL * pw[i - 1][0] * mod1) % mod2;
        pw[i][1] = (1LL * pw[i - 1][1] * mod2) % mod1;
    }
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, len = 0;
        string s, rs;
        cin >> n >> s;
        rs = s;
        reverse(rs.begin(), rs.end());
        hsh[0][0] = hsh[0][1] = {1, 1};
        for(int i = 1; i <= n; i++) {
            int c[2] = {s[i - 1] - '0' + 63, rs[i - 1] - '0' + 63};
            for(int j = 0; j < 2; j++) {
                hsh[i][j].f = (1LL * hsh[i - 1][j].f * mod1 + c[j]) % mod2;
                hsh[i][j].s = (1LL * hsh[i - 1][j].s * mod2 + c[j]) % mod1;
            }
        }
        for(int i = 1; i < n; i++) {
            if(get_hsh(0, n - i, n - 1) == get_hsh(1, 0, i - 1) && get_hsh(0, 0, n - i - 1) == get_hsh(1, i, n - 1)) {
                len = i;
            }
        }
        // len is the longest suffix that is also a prefix
        len = n - len;
        // output the prefix that comes before it
        cout << "Case #" << _ << ": " << s.substr(0, len) << endl;
    }
}