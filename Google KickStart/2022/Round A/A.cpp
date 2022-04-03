#include <bits/stdc++.h>

using namespace std;

int t;
string s1, s2;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> s1 >> s2;
        int n = s1.length(), m = s2.length();
        int pf = 0;
        for(int i = 0; i < m; i++) {
            if(pf < n && s2[i] == s1[pf]) {
                ++pf;
            }
        }
        cout << "Case #" << _ << ": ";
        if(pf == n) {
            cout << m - n << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
}