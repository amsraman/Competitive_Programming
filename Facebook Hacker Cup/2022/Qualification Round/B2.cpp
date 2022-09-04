#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int main() {
    ifstream cin("second_second_friend_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int r, c;
        cin >> r >> c;
        bool pos = true;
        vector<pair<int, int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        vector<string> grid(r), ans(r);
        vector<vector<int>> deg(r, vector<int>(c, 0));
        for(int i = 0; i < r; i++) {
            cin >> grid[i];
            for(int j = 0; j < c; j++) {
                ans[i] += '^';
                for(pair<int, int> d: dir) {
                    deg[i][j] += ((i + d.f >= 0) && (i + d.f < r) && (j + d.s >= 0) && (j + d.s < c));
                }
            }
        }
        queue<pair<int, int>> q;
        auto rem = [&](int x, int y) {
            if(grid[x][y] == '^') {
                pos = false;
            }
            ans[x][y] = '.';
            for(pair<int, int> d: dir) {
                if(x + d.f >= 0 && x + d.f < r && y + d.s >= 0 && y + d.s < c) {
                    --deg[x + d.f][y + d.s];
                    if(ans[x + d.f][y + d.s] == '^') {
                        q.push({x + d.f, y + d.s});
                    }
                }
            }
        };
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(grid[i][j] == '#' || deg[i][j] <= 1) {
                    rem(i, j);
                }
            }
        }
        while(!q.empty()) {
            pair<int, int> tp = q.front(); q.pop();
            if(deg[tp.f][tp.s] <= 1 && ans[tp.f][tp.s] == '^') {
                rem(tp.f, tp.s);
            }
        }
        cout << "Case #" << _ << ": ";
        if(!pos) {
            cout << "Impossible" << endl;
        } else {
            cout << "Possible" << endl;
            for(int i = 0; i < r; i++) {
                for(int j = 0; j < c; j++) {
                    cout << (grid[i][j] == '#' ? '#' : ans[i][j]);
                }
                cout << endl;
            }
        }
    }
}