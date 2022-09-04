#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("second_second_meaning_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n;
        string s;
        cin >> n >> s;
        cout << "Case #" << _ << ": " << endl;
        for(int i = 0; i < n - 1; i++) {
            cout << char(s[0] ^ '.' ^ '-');
            for(int j = 0; j < 9; j++) {
                cout << (((i >> j) & 1) ? '.' : '-');
            }
            cout << endl;
        }
    }
}