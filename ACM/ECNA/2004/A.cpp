#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    string s; cin >> s;
    while(s != "0") {
        int n = (int) s.length();
        vector<ll> dp(n + 1, 0); dp[n] = 1;
        for(int i = n - 1; i >= 0; i--) {
            if(s[i] > '0') dp[i] = dp[i + 1];
            if((i < n - 1) && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) dp[i] += dp[i + 2];
        }
        cout << dp[0] << '\n';
        cin >> s;
    }
}