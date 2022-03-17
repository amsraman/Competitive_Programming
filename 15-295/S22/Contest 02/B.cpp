#include <bits/stdc++.h>

using namespace std;

int n, k, best[26][50], ans = 1000;
string s;
bool pos[26];

int main() {
    cin >> n >> k >> s;
    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < k; j++) {
            best[i][j] = 1000;
        }
    }
    for(char c: s) {
        pos[c - 'a'] = true;
        best[c - 'a'][0] = c - 'a' + 1;
    }
    for(int i = 0; i < 26; i++) {
        if(pos[i]) {
            for(int j = 1; j < k; j++) {
                for(int pv = 0; pv + 1 < i; pv++) {
                    best[i][j] = min(best[i][j], best[pv][j - 1] + i + 1);
                }
            }
            ans = min(ans, best[i][k - 1]);
        }
    }
    cout << (ans == 1000 ? -1 : ans) << '\n';
}