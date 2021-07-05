/*
ID: adisund1
TASK: checker
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int n, ans, prv[15], nxt[15];
bool diag1[27], diag2[27];
array<int,13> cur;
vector<array<int,13>> seq;

void search(int row) {
    if(row == n) {
        if(ans < 3) {
            seq.push_back(cur);
        }
        ++ans;
        return;
    }
    for(int col = nxt[0]; col <= n; col = nxt[col]) {
        if(!diag1[row - col + 13] && !diag2[row + col - 1]) {
            prv[nxt[col]] = prv[col];
            nxt[prv[col]] = nxt[col];
            diag1[row - col + 13] = diag2[row + col - 1] = true;
            cur[row] = col;
            search(row + 1);
            prv[nxt[col]] = nxt[prv[col]] = col;
            diag1[row - col + 13] = diag2[row + col - 1] = false;
        }
    }
}

int main() {
    ifstream cin("checker.in");
    ofstream cout("checker.out");
    cin >> n;
    for(int i = 0; i<=n; i++) {
        nxt[i] = i+1;
        prv[i+1] = i;
    }
    search(0);
    for(int i = 0; i<seq.size(); i++) {
        for(int j = 0; j<n; j++) {
            if(j > 0) {
                cout << " ";
            }
            cout << seq[i][j];
        }
        cout << '\n';
    }
    cout << ans << '\n';
}