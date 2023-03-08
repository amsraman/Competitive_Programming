/*
ID: adisund1
TASK: betsy
LANG: C++
*/
#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, ans;
pair<int,int> dir[4] = {{0,-1},{-1,0},{0,1},{1,0}};
bool blocked[7][7];

bool ok(int r, int c) {
    if(r < 0 || r >= n || c < 0 || c >= n) {
        return false;
    }
    return !blocked[r][c];
}

void search(int r, int c, int num_moves) {
    if(r == 0 && c == n - 1) {
        if(num_moves == n * n - 1) {
            ++ans;
        }
        return;
    }
    if(num_moves + r + n - c - 1 > n * n) {
        return;
    }
    bool split_check = (ok(r,c-1) && ok(r,c+1) && !ok(r-1,c) && !ok(r+1,c)) || (!ok(r,c-1) && !ok(r,c+1) && ok(r-1,c) && ok(r+1,c));
    if(split_check) {
        return;
    }
    bool corner_check = (ok(r+1,c) && ok(r,c+1) && !ok(r+1,c+1)) || (ok(r-1,c) && ok(r,c+1) && !ok(r-1,c+1)) 
                            || (ok(r+1,c) && ok(r,c-1) && !ok(r+1,c-1)) || (ok(r-1,c) && ok(r,c-1) && !ok(r-1,c-1));
    if(corner_check) {
        return;
    }
    blocked[r][c] = true;
    for(pair<int,int> d: dir) {
        if(ok(r+d.f,c+d.s)) {
            search(r+d.f,c+d.s,num_moves+1);
        }
    }
    blocked[r][c] = false;
}

int main() {
    ifstream cin("betsy.in");
    ofstream cout("betsy.out");
    cin >> n;
    search(0,0,0);
    cout << ans << endl;
}