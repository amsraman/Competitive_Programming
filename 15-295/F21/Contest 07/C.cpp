#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int k, cost[1001], num[1010][1010], ncr[2001][2001], ans;
string n;

int main() {
    cin >> n >> k;
    for(int i = 2; i <= 1000; i++) {
        cost[i] = cost[__builtin_popcount(i)] + 1;
    }
    ncr[0][0] = 1;
    for(int i = 1; i <= 2000; i++) {
        ncr[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            ncr[i][j] = (ncr[i - 1][j - 1] + ncr[i - 1][j]) % mod;
        }
    }
    int sz = n.length();
    num[sz][0] = 1;
    for(int i = 0; i <= 1000; i++) {
        for(int j = sz - 1; j >= 0; j--) {
            num[j][i] = num[j + 1][i - (n[j] == '1')];
            if(n[j] == '1') {
                num[j][i] = (num[j][i] + ncr[sz - j - 1][i]) % mod;
            }
        }
        if(cost[i] == k - 1) {
            // Find the number of numbers with length i less than n and add that to ans
            ans = (ans + num[0][i]) % mod;
        }
    }
    if(k == 0) {
        cout << 1 << endl;
    } else if(k == 1) {
        cout << (ans + mod - 2) % mod << endl;
    } else {
        cout << ans << endl;
    }
}