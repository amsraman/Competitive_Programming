#include <bits/stdc++.h>

using namespace std;

int t, cost[26];
string s, f;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> s >> f;
        int n = s.length();
        memset(cost, 5400, sizeof(cost));
        set<char> fc;
        for(char c: f) {
            fc.insert(c);
        }
        for(int i = 0; i < 26; i++) {
            int lc = 0, rc = 0;
            char tl = i, tr = i;
            while(!fc.count(char('a' + tl))) {
                tl = (tl + 25) % 26;
                ++lc;
            }
            while(!fc.count(char('a' + tr))) {
                tr = (tr + 1) % 26;
                ++rc;
            }
            cost[i] = min(lc, rc);
        }
        int ans = 0;
        for(char c: s) {
            ans += cost[c - 'a'];
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}