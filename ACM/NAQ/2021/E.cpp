#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin >> s;
    int n = s.length();
    bool correct = (n & 1 ^ 1);
    for(int i = 0; i < n; i++) {
        char exp = '|';
        if(i == n / 2 - 1) {
            exp = '(';
        } else if(i == n / 2) {
            exp = ')';
        }
        correct &= (s[i] == exp);
    }
    cout << (correct ? "correct" : "fix") << '\n';
}