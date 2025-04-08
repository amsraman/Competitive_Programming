#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<string> row_ref(n), col_ref(m);
    vector<vector<char>> ans(n, vector<char>(m, '?'));
    for(int i = 0, p; i < n; i++) {
        cin >> p;
        for(int j = 0, v; j < p; j++) {
            cin >> v;
            for(int k = 0; k < v; k++) row_ref[i] += "X";
            if(j < p - 1) row_ref[i] += ".";
        }
        row_ref[i] = "." + row_ref[i] + ".";
    }
    for(int i = 0, p; i < m; i++) {
        cin >> p;
        for(int j = 0, v; j < p; j++) {
            cin >> v;
            for(int k = 0; k < v; k++) col_ref[i] += "X";
            if(j < p - 1) col_ref[i] += ".";
        }
        col_ref[i] = "." + col_ref[i] + ".";
    }
    while(true) {
        bool ch = false;
        for(int i = 0; i < n; i++) {
            int sz = row_ref[i].length();
            vector<vector<bool>> dp1(m + 2, vector<bool>(sz + 2, false)), dp2(m + 2, vector<bool>(sz + 2, false));
            dp1[0][0] = dp2[m + 1][sz - 1] = true;
            for(int j = 1; j <= m + 1; j++) {
                for(int k = 0; k < sz; k++) {
                    if(row_ref[i][k] == '.' && (j == m + 1 || ans[i][j - 1] != 'X')) { // place white
                        dp1[j][k] = dp1[j - 1][k];
                        if(k > 0) dp1[j][k] = (dp1[j][k] | dp1[j - 1][k - 1]);
                    }
                    if(k > 0 && row_ref[i][k] == 'X' && j <= m && ans[i][j - 1] != '.') { // place black
                        dp1[j][k] = (dp1[j][k] | dp1[j - 1][k - 1]);
                    }
                }
            }
            for(int j = m; j >= 0; j--) {
                for(int k = sz - 1; k >= 0; k--) {
                    if(row_ref[i][k] == '.' && (j == 0 || ans[i][j - 1] != 'X')) { // place white
                        dp2[j][k] = dp2[j + 1][k];
                        if(k < sz - 1) dp2[j][k] = (dp2[j][k] | dp2[j + 1][k + 1]);
                    }
                    if(k < sz - 1 && row_ref[i][k] == 'X' && j > 0 && ans[i][j - 1] != '.') { // place black
                        dp2[j][k] = (dp2[j][k] | dp2[j + 1][k + 1]);
                    }
                }
            }
            for(int j = 1; j <= m; j++) {
                bool bl = false, wh = false;
                for(int k = 0; k <= sz + 1; k++) {
                    if(dp1[j][k] && dp2[j][k]) {
                        if(row_ref[i][k] == 'X') bl = true;
                        if(row_ref[i][k] == '.') wh = true;
                    }
                }
                if((!bl || !wh) && ans[i][j - 1] == '?') ch = true;
                if(!bl) ans[i][j - 1] = '.';
                if(!wh) ans[i][j - 1] = 'X';
            }
        }
        for(int j = 0; j < m; j++) {
            int sz = col_ref[j].length();
            vector<vector<bool>> dp1(n + 2, vector<bool>(sz, false)), dp2(n + 2, vector<bool>(sz, false));
            dp1[0][0] = dp2[n + 1][sz - 1] = true;
            for(int i = 1; i <= n + 1; i++) {
                for(int k = 0; k < sz; k++) {
                    if(col_ref[j][k] == '.' && (i == n + 1 || ans[i - 1][j] != 'X')) { // place white
                        dp1[i][k] = dp1[i - 1][k];
                        if(k > 0) dp1[i][k] = (dp1[i][k] | dp1[i - 1][k - 1]);
                    }
                    if(k > 0 && col_ref[j][k] == 'X' && i <= n && ans[i - 1][j] != '.') { // place black
                        dp1[i][k] = (dp1[i][k] | dp1[i - 1][k - 1]);
                    }
                }
            }
            for(int i = n; i >= 0; i--) {
                for(int k = sz - 1; k >= 0; k--) {
                    if(col_ref[j][k] == '.' && (i == 0 || ans[i - 1][j] != 'X')) { // place white
                        dp2[i][k] = dp2[i + 1][k];
                        if(k < sz - 1) dp2[i][k] = (dp2[i][k] | dp2[i + 1][k + 1]);
                    }
                    if(k < sz - 1 && col_ref[j][k] == 'X' && i > 0 && ans[i - 1][j] != '.') { // place black
                        dp2[i][k] = (dp2[i][k] | dp2[i + 1][k + 1]);
                    }
                }
            }
            for(int i = 1; i <= n; i++) {
                bool bl = false, wh = false;
                for(int k = 0; k <= sz + 1; k++) {
                    if(dp1[i][k] && dp2[i][k]) {
                        if(col_ref[j][k] == 'X') bl = true;
                        if(col_ref[j][k] == '.') wh = true;
                    }
                }
                if((!bl || !wh) && ans[i - 1][j] == '?') ch = true;
                if(!bl) ans[i - 1][j] = '.';
                if(!wh) ans[i - 1][j] = 'X';
            }
        }
        if(!ch) break;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}