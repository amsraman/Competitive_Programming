#include <bits/stdc++.h>

using namespace std;

int t, n;
bool bad[64][2];
string s;

bool isPalin(int msk, int len) {
    vector<int> dig;
    while(msk > 0) {
        dig.push_back(msk & 1);
        msk >>= 1;
    }
    while(dig.size() < len) {
        dig.push_back(0);
    }
    for(int i = 0, j = len - 1; i < j; i++, j--) {
        if(dig[i] != dig[j]) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> t;
    for(int i = 0; i < 64; i++) {
        if(isPalin(i & 31, 5)) {
            bad[i][0] = true;
        }
        if(isPalin(i, 6)) {
            bad[i][1] = true;
        }
    }
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> s;
        vector<vector<bool>> dp(n, vector<bool>(64, false));
        if(s[0] == '0') {
            dp[0][0] = true;
        } else if(s[0] == '1') {
            dp[0][1] = true;
        } else {
            dp[0][0] = dp[0][1] = true;
        }
        for(int i = 1; i < n; i++) {
            vector<bool> acc(2, false);
            if(s[i] == '0') {
                acc[0] = 1;
            } else if(s[i] == '1') {
                acc[1] = 1;
            } else {
                acc[0] = acc[1] = 1;
            }
            for(int j = 0; j < 64; j++) {
                if(acc[j & 1] && (dp[i - 1][j >> 1] || dp[i - 1][(j >> 1) + 32]) && (i < 4 || !bad[j][0]) && (i < 5 || !bad[j][1])) {
                    dp[i][j] = true;
                }
            }
        }
        bool ans = false;
        for(int i = 0; i < 64; i++) {
            ans |= dp[n - 1][i];
        }
        cout << "Case #" << _ << ": " << (ans ? "POSSIBLE" : "IMPOSSIBLE") << endl;
    }
}