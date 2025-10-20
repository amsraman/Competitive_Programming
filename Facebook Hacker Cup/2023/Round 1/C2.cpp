#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ifstream cin("back_in_black_chapter_2_input.txt");
    ofstream cout("output.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, q; string s; cin >> n >> s >> q;
        assert(s.length() == n);
        vector<int> b(q);
        vector<bool> press(n, false);
        int cur = 0; ll ans = 0;
        for(int i = 1; i <= n; i++) {
            if(s[i - 1] == '1') {
                press[i - 1] = true, ++cur;
                for(int j = i; j <= n; j += i) {
                    s[j - 1] ^= '0' ^ '1';
                }
            }
        }
        for(int i = 0; i < q; i++) {
            cin >> b[i]; --b[i];
            if(press[b[i]]) press[b[i]] = false, --cur;
            else press[b[i]] = true, ++cur;
            ans += cur;
        }
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}