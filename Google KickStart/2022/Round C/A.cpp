#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n;
        string s;
        cin >> n >> s;
        vector<bool> cat(4, false);
        vector<char> cand(4);
        cand[0] = 'A', cand[1] = 'a', cand[2] = '1', cand[3] = '&';
        for(char c: s) {
            if(c == '#' || c == '@' || c == '*' || c == '&') {
                cat[3] = true;
            } else if(isdigit(c)) {
                cat[2] = true;
            } else if(c == toupper(c)) {
                cat[0] = true;
            } else {
                cat[1] = true;
            }
        }
        for(int i = 0; i < 4; i++) {
            if(!cat[i]) {
                s += cand[i];
            }
        }
        while(s.length() < 7) {
            s += '1';
        }
        cout << "Case #" << _ << ": " << s << endl;
    }
}