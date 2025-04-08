#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    vector<string> grid(n);
    for(int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    string mes; cin >> mes; int pos = n * n - 1;
    map<pair<int, int>, char> mp;
    bool bad = false;
    for(int it = 0; it < 4; it++) {
        vector<string> g1 = grid;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                g1[i][j] = grid[j][n - i - 1];
            }
        }
        grid = g1;
        for(int i = n - 1; i >= 0; i--) {
            for(int j = n - 1; j >= 0; j--) {
                if(grid[i][j] == '.') {
                    if(pos < 0) {
                        bad = true;
                    } else {
                        char lst = mes[pos--];
                        if(mp.count({i, j}) && mp[{i, j}] != lst) {
                            bad = true;
                        } else {
                            mp[{i, j}] = lst;
                        }
                    }
                }
            }
        }
    }
    if(mp.size() != n * n || bad) {
        cout << "invalid grille\n";
    } else {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << mp[{i, j}];
            }
        }
        cout << '\n';
    }
}