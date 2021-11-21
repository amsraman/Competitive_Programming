#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int t, n, num[800000];
string s;

int main() {
    freopen("weak_typing_chapter_2_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> s;
        int ans = 0;
        char lst = s[0];
        int pos = (lst == 'F' ? -1 : 0);
        for(int i = 1; i < n; i++) {
            num[i] = num[i - 1];
            if(s[i] == 'O' || s[i] == 'X') {
                if(lst != s[i] && lst != 'F') {
                    num[i] = (num[i] + pos + 1) % mod;
                }
                lst = s[i];
                pos = i;
            }
            ans = (ans + num[i]) % mod;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}