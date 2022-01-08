#include <bits/stdc++.h>

using namespace std;

int t, n[3], vc[3], yc[3];
set<char> vs;

int main() {
    vs.insert('a'), vs.insert('e'), vs.insert('i'), vs.insert('o'), vs.insert('u');
    vs.insert('A'), vs.insert('E'), vs.insert('I'), vs.insert('O'), vs.insert('U');
    cin >> t;
    while(t--) {
        cin >> n[0] >> n[1] >> n[2];
        for(int i = 0; i < 3; i++) {
            vc[i] = yc[i] = 0;
            for(int j = 0; j < n[i]; j++) {
                string s;
                cin >> s;
                for(char c: s) {
                    if(vs.count(c)) {
                        ++vc[i];
                    }
                    if(c == 'y' || c == 'Y') {
                        ++yc[i];
                    }
                }
            }
        }
        bool ok = true;
        ok &= (vc[0] <= 5 && vc[0] + yc[0] >= 5);
        ok &= (vc[1] <= 7 && vc[1] + yc[1] >= 7);
        ok &= (vc[2] <= 5 && vc[2] + yc[2] >= 5);
        cout << (ok ? "YES" : "NO") << endl;
    }
}
