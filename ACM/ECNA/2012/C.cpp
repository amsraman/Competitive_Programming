#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        vector<vector<int>> pts(7, vector<int>(6));
        for(int i = 0; i < 7; i++) {
            for(int j = 0; j < 6; j++) {
                cin >> pts[i][j]; --pts[i][j];
            }
        }
        cout << "Case " << _ << ":";
        vector<int> perm(7);
        iota(perm.begin(), perm.end(), 0);
        bool found = false;
        vector<int> ind(6);
        vector<vector<int>> pos(7, vector<int>(6));
        for(int i = 0; i < 7; i++) {
            for(int j = 0; j < 6; j++) {
                pos[i][pts[i][j]] = j;
            }
        }
        do {
            bool ok = true;
            for(int i = 0; i < 6; i++) {
                int i1 = pos[perm[i + 1]][pts[perm[0]][i]];
                int i2 = pos[perm[(i + 1) % 6 + 1]][pts[perm[0]][(i + 1) % 6]];
                int num1 = pts[perm[i + 1]][(i1 + 5) % 6];
                int num2 = pts[perm[(i + 1) % 6 + 1]][(i2 + 1) % 6];
                if(num1 != num2) {
                    ok = false;
                }
            }
            if(ok) {
                int st = 0;
                cout << " " << perm[0];
                while(pts[perm[0]][st] != 0) ++st;
                for(int i = 0; i < 6; i++) {
                    cout << " " << perm[1 + (i + st) % 6];
                }
                cout << '\n';
                found = true;
                break;
            }
        } while(next_permutation(perm.begin(), perm.end()));
        if(!found) {
            cout << " No solution\n";
        }
    }
}