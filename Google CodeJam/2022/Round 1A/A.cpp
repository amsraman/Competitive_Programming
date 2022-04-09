#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t;
string s;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> s;
        int n = s.length();
        vector<pair<char, int>> crs;
        for(int i = 0, j = 0; i < n; i++) {
            j++;
            if(i == n - 1 || s[i] != s[i + 1]) {
                crs.push_back({s[i], j});
                j = 0;
            }
        }
        cout << "Case #" << _ << ": ";
        n = crs.size();
        for(int i = 0; i < n - 1; i++) {
            for(int j = 0; j < crs[i].s; j++) {
                cout << crs[i].f;
            }
            if(crs[i].f < crs[i + 1].f) {
                for(int j = 0; j < crs[i].s; j++) {
                    cout << crs[i].f;
                }
            }
        }
        for(int j = 0; j < crs[n - 1].s; j++) {
            cout << crs[n - 1].f;
        }
        cout << endl;
    }
}