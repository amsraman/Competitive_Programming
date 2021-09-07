#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, co[26];
pair<char, int> pos[10000];
string s;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        memset(co, 0, sizeof(co));
        cin >> s;
        int n = s.length();
        for(char c: s) {
            ++co[(c - 'a')];
        }
        int mx = 0;
        for(int i = 0; i < 26; i++) {
            mx = max(mx, co[i]);
        }
        cout << "Case #" << _ << ": ";
        if(mx * 2 > n) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            string ret = s;
            for(int i = 0; i < n; i++) {
                pos[i] = {s[i], i};
            }
            sort(pos, pos + n);
            for(int i = 0; i < n; i++) {
                ret[pos[i].s] = pos[(i + mx) % n].f;
            }
            cout << ret << endl;
        }
    }
}