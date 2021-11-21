#include <bits/stdc++.h>

using namespace std;

int t, n;
string p;

int main() {
    cin >> t;
    set<char> rc, bc, yc;
    rc.insert('R'), rc.insert('O'), rc.insert('P'), rc.insert('A');
    bc.insert('B'), bc.insert('G'), bc.insert('P'), bc.insert('A');
    yc.insert('Y'), yc.insert('G'), yc.insert('O'), yc.insert('A');
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> p;
        int ans = 0;
        for(int i = 0; i < n; i++) {
            if(rc.count(p[i]) && (i == n - 1 || !rc.count(p[i + 1]))) {
                ++ans;
            }
            if(bc.count(p[i]) && (i == n - 1 || !bc.count(p[i + 1]))) {
                ++ans;
            }
            if(yc.count(p[i]) && (i == n - 1 || !yc.count(p[i + 1]))) {
                ++ans;
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}