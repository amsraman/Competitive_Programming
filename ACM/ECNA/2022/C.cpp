#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n; cin >> n;
    map<char, int> frq; string ranks = "A23456789TJQK";
    vector<ll> dp(16, 0); dp[0] = 1; ll ans = 0;
    for(int i = 0; i < n; i++) {
        char c; cin >> c;
        int pt = c - '0';
        if(c == 'A') pt = 1;
        if(c == 'T' || c == 'J' || c == 'Q' || c == 'K') pt = 10;
        for(int j = 15; j >= pt; j--) {
            dp[j] += dp[j - pt];
        }
        ans += 2 * frq[c]; ++frq[c];
    }
    ans += 2 * dp[15];
    for(int i = 0; i < 13;) {
        int j = i - 1; ll tot = 1;
        while(j < 12 && frq.count(ranks[j + 1])) {
            tot *= frq[ranks[++j]];
        }
        if(j >= i + 2) {
            ans += tot * (j - i + 1);
        }
        i = max(i, j) + 1;
    }
    cout << ans << '\n';
}