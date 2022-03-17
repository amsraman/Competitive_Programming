#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin >> s;
    int n = s.length();
    int rot1 = 0, rot2 = 0;
    for(int i = 0; i < n; i++) {
        if(i < n / 2) {
            rot1 = (rot1 + s[i] - 'A') % 26;
        } else {
            rot2 = (rot2 + s[i] - 'A') % 26;
        }
    }
    for(int i = 0; i < n; i++) {
        if(i < n / 2) {
            s[i] = char('A' + (s[i] - 'A' + rot1) % 26);
        } else {
            s[i] = char('A' + (s[i] - 'A' + rot2) % 26);
        }
    }
    for(int i = 0; i < n / 2; i++) {
        cout << char('A' + ((s[i] - 'A') + (s[i + n / 2] - 'A')) % 26);
    }
    cout << endl;
}