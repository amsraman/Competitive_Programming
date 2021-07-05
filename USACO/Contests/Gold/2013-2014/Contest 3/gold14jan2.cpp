#include <bits/stdc++.h>

using namespace std;

int n, m, r[101][101], s[101][101], rps[101][101], sps[101][101];
string grid[100];

int get_sum(int x, int y, int len, bool type) {
    if(type) {
        return (rps[x+len][y+len]-rps[x+len][y]-rps[x][y+len]+rps[x][y]);
    } else {
        return (sps[x+len][y+len]-sps[x+len][y]-sps[x][y+len]+sps[x][y]);
    }
}

bool ok(int x) {
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++) {
            r[i][j] = (grid[i][j] == 'R');
            s[i][j] = (grid[i][j] == 'S');
        }
    }
    int num_covered = 0;
    while(num_covered < n * m) {
        // Recalculate Prefix Sums
        for(int i = 0; i<n; i++) {
            for(int j = 0; j<m; j++) {
                rps[i+1][j+1] = rps[i+1][j] + rps[i][j+1] - rps[i][j] + r[i][j];
                sps[i+1][j+1] = sps[i+1][j] + sps[i][j+1] - sps[i][j] + s[i][j];
            }
        }
        // Look for next move
        int next_x = -1, next_y = -1;
        for(int i = 0; i<=n-x; i++) {
            for(int j = 0; j<=m-x; j++) {
                if((get_sum(i,j,x,0)==x*x)^(get_sum(i,j,x,1)==x*x)) {
                    next_x = i, next_y = j;
                }
            }
        }
        if(next_x != -1) {
            for(int i = 0; i<x; i++) {
                for(int j = 0; j<x; j++) {
                    num_covered += (r[next_x+i][next_y+j]^s[next_x+i][next_y+j]);
                    r[next_x+i][next_y+j] = s[next_x+i][next_y+j] = 1;
                }
            }
        } else {
            break;
        }
    }
    return num_covered == n*m;
}

int main() {
    ifstream cin("skicourse.in");
    ofstream cout("skicourse.out");
    cin >> n >> m;
    for(int i = 0; i<n; i++) {
        cin >> grid[i];
    }
    int lb = 1, ub = min(n,m);
    while(lb < ub) {
        int mid = (lb + ub + 1)/2;
        if(ok(mid)) {
            lb = mid;
        } else {
            ub = mid - 1;
        }
    }
    cout << ub << endl;
}