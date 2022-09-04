#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("second_friend_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int r, c, num = 0;
        cin >> r >> c;
        vector<string> grid(r);
        for(int i = 0; i < r; i++) {
            cin >> grid[i];
            for(int j = 0; j < c; j++) {
                num += grid[i][j] == '^';
            }
        }
        cout << "Case #" << _ << ": ";
        if(num > 0 && min(r, c) == 1) {
            cout << "Impossible" << endl;
        } else {
            cout << "Possible" << endl;
            for(int i = 0; i < r; i++) {
                for(int j = 0; j < c; j++) {
                    cout << (min(r, c) == 1 ? '.' : '^');
                }
                cout << endl;
            }
        }
    }
}