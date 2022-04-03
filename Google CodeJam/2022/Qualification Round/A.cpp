#include <bits/stdc++.h>

using namespace std;

int t, r, c;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> r >> c;
        cout << "Case #" << _ << ": " << endl << "..+";
        for(int i = 1; i < c; i++) {
            cout << "-+";
        }
        cout << endl << '.';
        for(int i = 0; i < c; i++) {
            cout << ".|";
        }
        cout << endl << "+";
        for(int i = 0; i < c; i++) {
            cout << "-+";
        }
        cout << endl;
        for(int i = 1; i < r; i++) {
            cout << '|';
            for(int j = 0; j < c; j++) {
                cout << ".|";
            }
            cout << endl << '+';
            for(int j = 0; j < c; j++) {
                cout << "-+";
            }
            cout << endl;
        }
    }
}