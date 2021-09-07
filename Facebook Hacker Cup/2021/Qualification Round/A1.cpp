#include <bits/stdc++.h>

using namespace std;

int t, n;
string s;

bool vowel(char c) {
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

int main() {
    freopen("consistency_chapter_1_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> s;
        n = s.length();
        int ans = 0x3f3f3f3f;
        for(int i = 0; i < 26; i++) {
            int cnt = 0;
            for(int j = 0; j < n; j++) {
                if(s[j] == char('A' + i)) {
                    continue;
                }
                if(vowel(s[j]) ^ vowel(char('A' + i))) {
                    ++cnt;
                } else {
                    cnt += 2;
                }
            }
            ans = min(ans, cnt);
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}