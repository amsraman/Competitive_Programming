#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll x, y, ncr[21][21];

ll exp(ll b, ll p) {
    ll ret = 1;
    while(p) {
        if(p & 1) {
            ret *= b;
        }
        b *= b, p >>= 1;
    }
    return ret;
}

ll get_num(vector<int> & used, int len) {
    int rem_len = len - used.size();
    array<int, 10> cts; cts.fill(0);
    for(int i: used) {
        ++cts[i];
    }
    vector<int> unique_digits;
    for(int i = 0; i < 10; i++) {
        if(cts[i] > 0) {
            unique_digits.push_back(i);
        }
    }
    ll ret = 0;
    // Case on the majority digit
    for(int d = 0; d < 10; d++) {
        // Case on the number of times this appears (> len / 2)
        for(int l = (1 + len) / 2; l <= len; l++) {
            int necessary = l - cts[d];
            if(necessary < 0 || necessary > rem_len) {
                continue;
            }
            ret += ncr[rem_len][necessary] * exp(9, rem_len - necessary);
        }
    }
    // Special Case: Two Majorities
    if(unique_digits.size() == 1 && len % 2 == 0 && rem_len >= len / 2) {
        ret -= 9 * ncr[rem_len][len / 2];
    } else if(unique_digits.size() == 2 && len % 2 == 0 && len / 2 >= cts[unique_digits[0]]) {
        ret -= ncr[rem_len][len / 2 - cts[unique_digits[0]]];
    }
    return ret;
}

ll f(ll num) {
    ll ret = 0;
    vector<int> dig, cur;
    while(num > 0) {
        dig.push_back(num % 10);
        num /= 10;
    }
    reverse(dig.begin(), dig.end());
    cur.push_back(1);
    for(int i = 1; i < dig.size(); i++) {
        ret += 9 * get_num(cur, i);
    }
    cur.pop_back();
    for(int i = 0; i < dig.size(); i++) {
        for(int j = (i == 0); j < dig[i]; j++) {
            cur.push_back(j);
            ret += get_num(cur, dig.size());
            cur.pop_back();
        }
        cur.push_back(dig[i]);
    }
    ret += get_num(cur, dig.size());
    return ret;
}

int main() {
    ifstream cin("odometer.in");
    ofstream cout("odometer.out");
    cin >> x >> y;
    ncr[0][0] = 1;
    for(int i = 1; i <= 20; i++) {
        ncr[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            ncr[i][j] = ncr[i - 1][j - 1] + ncr[i - 1][j];
        }
    }
    cout << f(y) - f(x - 1) << endl;
}
