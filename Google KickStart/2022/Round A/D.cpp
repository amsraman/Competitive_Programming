#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t;
ll a, b, p9[13], num[109][13][109][109];

int ok(string x) {
    for(char c: x) {
        if(c == '0') {
            return 0;
        }
    }
    int sum = 0;
    for(char c: x) {
        sum += c - '0';
    }
    int prod = 1;
    for(char c: x) {
        prod = (prod * (c - '0')) % sum;
    }
    return (prod == 0);
}

ll f(ll n) {
    // Find the number of satisfying numbers <= x
    string x = to_string(n);
    int len = x.length();
    ll ret = 0;
    // Take care of zeros independently
    for(int i = 1; i < len; i++) {
        ret += p9[i];
    }
    bool broken = false;
    for(int i = 0; i < len; i++) {
        if(x[i] == '0') {
            broken = true;
            break;
        }
        ret += (x[i] - '0' - 1) * p9[len - i - 1];
    }
    ret += (int) (!broken);
    ret = n - ret;
    for(int sum = 1; sum <= 108; sum++) {
        // Work with numbers that have length < len
        for(int i = 1; i < len; i++) {
            ret += num[sum][i][0][sum];
        }
        int rs = 0, rp = 1;
        // Case on the first digit that is not pressed against the top
        for(int i = 0; i < len; i++) {
            int cur_dig = x[i] - '0';
            for(int j = 1; j < cur_dig; j++) {
                // Case on what the last digit is
                // Accumulate the number of ways to assign the remaining that satisfy this
                int ds = sum - rs - j, tp = (rp * j) % sum;
                for(int k = 0; k <= sum; k++) {
                    if(ds >= 0 && (k * tp) % sum == 0) {
                        ret += num[sum][len - i - 1][k][ds];
                    }
                }
            }
            rs += cur_dig;
            rp = (rp * cur_dig) % sum;
            if(rs > sum || cur_dig == 0) {
                break;
            }
        }
    }
    // Account for the case where x itself is special
    return ret + ok(x);
}

int main() {
    p9[0] = 1;
    for(int i = 1; i < 13; i++) {
        p9[i] = p9[i - 1] * 9;
    }
    // Deal with leading zeros somehow later
    for(int i = 1; i <= 108; i++) {
        num[i][0][1][0] = 1;
        for(int j = 0; j < 12; j++) {
            for(int pm = 0; pm <= i; pm++) {
                for(int sm = 0; sm <= i; sm++) {
                    for(int d = 1; d < 10; d++) {
                        if(sm + d <= i) {
                            num[i][j + 1][(pm * d) % i][sm + d] += num[i][j][pm][sm];
                        }
                    }
                }
            }
        }
    }
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> a >> b;
        cout << "Case #" << _ << ": " << f(b) - f(a - 1) << endl;
    }
}