#include <bits/stdc++.h>

using namespace std;

int t, g[3][3], ans;

void try_val(int x) {
    int num = 0;
    g[1][1] = x;
    for(int i = 0; i<3; i++) {
        if(2 * g[i][1] == g[i][0] + g[i][2]) {
            ++num;
        }
        if(2 * g[1][i] == g[0][i] + g[2][i]) {
            ++num;
        }
    }
    if(2 * g[1][1] == g[0][0] + g[2][2]) {
        ++num;
    }
    if(2 * g[1][1] == g[0][2] + g[2][0]) {
        ++num;
    }
    ans = max(ans,num);
}

int main() {
    cin >> t;
    for(int _ = 1; _<=t; _++) {
        cin >> g[0][0] >> g[0][1] >> g[0][2] >> g[1][0] >> g[1][2] >> g[2][0] >> g[2][1] >> g[2][2];
        ans = 0;
        try_val((g[1][0]+g[1][2])/2);
        try_val((g[0][1]+g[2][1])/2);
        try_val((g[0][0]+g[2][2])/2);
        try_val((g[2][0]+g[0][2])/2);
        cout << "Case #" << _ << ": " << ans << endl;
    }
}