#include <bits/stdc++.h>

using namespace std;

int n, ans[5000];
bool palin[5000][5000], k_palin[5000][5000][2];
string s;

int main() {
    cin >> s;
    n = s.length();
    for(int i = 0; i < n; i++) {
        int lb = i, ub = i;
        while(lb >= 0 && ub < n && s[lb] == s[ub]) {
            palin[lb][ub] = true;
            k_palin[lb][ub][0] = true, ++ans[0];
            --lb, ++ub;
        }
        lb = i, ub = i + 1;
        while(lb >= 0 && ub < n && s[lb] == s[ub]) {
            palin[lb][ub] = true;
            k_palin[lb][ub][0] = true, ++ans[0];
            --lb, ++ub;
        }
    }
    for(int k = 1; k < n; k++) {
        bool match = false;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                k_palin[i][j][k & 1] = false;
            }
        }
        for(int i = 0; i < n; i++) {
            int lb = i, ub = i;
            while(lb >= 0 && ub < n && s[lb] == s[ub]) {
                if(palin[lb][ub] && k_palin[lb][i - 1][k & 1 ^ 1] && k_palin[i + 1][ub][k & 1 ^ 1]) {
                    k_palin[lb][ub][k & 1] = true;
                    ++ans[k];
                    match = true;
                }
                --lb, ++ub;
            }
            lb = i, ub = i + 1;
            while(lb >= 0 && ub < n && s[lb] == s[ub]) {
                if(palin[lb][ub] && k_palin[lb][i][k & 1 ^ 1] && k_palin[i + 1][ub][k & 1 ^ 1]) {
                    k_palin[lb][ub][k & 1] = true;
                    ++ans[k];
                    match = true;
                }
                --lb, ++ub;
            }
        }
        if(!match) {
            break;
        }
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}