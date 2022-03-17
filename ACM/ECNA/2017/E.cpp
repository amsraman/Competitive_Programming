#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, nc;
bool isa[500][500], hasa[500][500];
map<string, int> ind;

void ins(string s) {
    if(!ind.count(s)) {
        isa[nc][nc] = true;
        ind[s] = nc++;
    }
}

void dfs(int x, int y) {
    hasa[x][y] = true;
    for(int i = 0; i < nc; i++) {
        if(isa[i][x] && !hasa[i][y]) {
            dfs(i, y);
        }
    }
    for(int i = 0; i < nc; i++) {
        if(isa[y][i] && !hasa[x][i]) {
            dfs(x, i);
        }
    }
}

int main() {
    cin >> n >> m;
    vector<pair<int, int>> hases;
    for(int i = 0; i < n; i++) {
        string p1, rel, p2;
        cin >> p1 >> rel >> p2;
        ins(p1), ins(p2);
        if(rel == "is-a") {
            isa[ind[p1]][ind[p2]] = true;
        } else {
            hasa[ind[p1]][ind[p2]] = true;
        }
    }
    for(int k = 0; k < nc; k++) {
        for(int i = 0; i < nc; i++) {
            for(int j = 0; j < nc; j++) {
                if(isa[i][k] && isa[k][j]) {
                    isa[i][j] = true;
                }
                if(hasa[i][k] && hasa[k][j]) {
                    hasa[i][j] = true;
                }
            }
        }
    }
    for(int i = 0; i < nc; i++) {
        for(int j = 0; j < nc; j++) {
            if(hasa[i][j]) {
                dfs(i, j);
            }
        }
    }
    for(int k = 0; k < nc; k++) {
        for(int i = 0; i < nc; i++) {
            for(int j = 0; j < nc; j++) {
                if(hasa[i][k] && hasa[k][j]) {
                    hasa[i][j] = true;
                }
            }
        }
    }
    for(int i = 0; i < m; i++) {
        string p1, rel, p2;
        cin >> p1 >> rel >> p2;
        cout << "Query " << i + 1 << ": ";
        if(rel == "is-a") {
            cout << (isa[ind[p1]][ind[p2]] ? "true" : "false");
        } else {
            cout << (hasa[ind[p1]][ind[p2]] ? "true" : "false");
        }
        cout << '\n';
    }
}