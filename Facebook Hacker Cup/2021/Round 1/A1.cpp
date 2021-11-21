#include <bits/stdc++.h>

using namespace std;

int t, n;
string s;

int main() {
    freopen("weak_typing_chapter_1_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> s;
        char lst = 'F';
        int ans = 0;
        for(char c: s) {
            if(c == 'O' && lst != c) {
                ans += (lst == 'X');
                lst = 'O';
            }
            if(c == 'X' && lst != c) {
                ans += (lst == 'O');
                lst = 'X';
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}