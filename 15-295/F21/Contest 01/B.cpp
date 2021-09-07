#include <bits/stdc++.h>

using namespace std;

int n, h[101], v[101];
bool ans = true;
string s;

int main() {
    cin >> s;
    n = s.length();
    for(int i = 0; i < n; i++) {
        h[i + 1] = h[i], v[i + 1] = v[i];
        if(s[i] == 'U') {
            --h[i + 1];
        } else if(s[i] == 'D') {
            ++h[i + 1];
        } else if(s[i] == 'L') {
            --v[i + 1];
        } else {
            ++v[i + 1];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = i + 2; j <= n; j++) {
            if(abs(h[j] - h[i]) + abs(v[j] - v[i]) < 2) {
                ans = false;
            }
        }
    }
    cout << (ans ? "OK" : "BUG") << endl;
}