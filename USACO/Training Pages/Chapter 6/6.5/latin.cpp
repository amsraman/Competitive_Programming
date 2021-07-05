/*
ID: adisund1
TASK: latin
LANG: C++
*/
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, prv[10][10], nxt[10][10];
ll ans, fact[7] = {1,1,2,6,24,120,720};
bool col[10][10];

void fix_point(int r, int c, int num, bool on) {
    col[c][num-1] = on;
    if(on) {
        nxt[r][prv[r][num]] = nxt[r][num];
        prv[r][nxt[r][num]] = prv[r][num];
    } else {
        nxt[r][prv[r][num]] = num;
        prv[r][nxt[r][num]] = num;
    }
}

void search(int r, int c) {
    if(r == n-1) {
        ++ans;
        return;
    }
    for(int i = nxt[r][0]; i <= n; i = nxt[r][i]) {
        if(!col[c][i-1]) {
            fix_point(r,c,i,true);
            if(c < n-2 || !col[n-1][nxt[r][0]-1]) {
                if(c == n-2) {
                    col[n-1][nxt[r][0]-1] = true;
                }
                int nxt_r = (c == n-2 ? r+1 : r);
                int nxt_c = (c == n-2 ? 1 : c+1);
                search(nxt_r,nxt_c);
                if(c == n-2) {
                    col[n-1][nxt[r][0]-1] = false;
                }
            }
            fix_point(r,c,i,false);
        }
    }
}

ll from_permutation(string perm) {
    for(int i = 0; i<n; i++) {
        col[i][perm[i]-'0'] = true;
    }
    ans = 0;
    search(2,1);
    for(int i = 0; i<n; i++) {
        col[i][perm[i]-'0'] = false;
    }
    return ans;
}

int main() {
    ifstream cin("latin.in");
    ofstream cout("latin.out");
    cin >> n;
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<=n; j++) {
            nxt[i][j] = j+1, prv[i][j+1] = j;
        }
        fix_point(0,i,i+1,true);
        fix_point(i,0,i+1,true);
    }
    if(n > 6) {
        ll tot = 0;
        tot += from_permutation("1034562") * 24;
        tot += from_permutation("1032564") * 20;
        tot += from_permutation("1204563") * 30;
        tot += from_permutation("1204365") * 15;
        tot += from_permutation("1230564") * 40;
        tot += from_permutation("1234065") * 60;
        tot += from_permutation("1234560") * 120;
        ans = tot;
    } else {
        search(1,1);
    }
    cout << ans * fact[n-1] << '\n';
}