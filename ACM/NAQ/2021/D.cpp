#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int n, nc;
vector<string> tokens[100];
map<string, int> ind;

void ins(string s) {
    if(ind.count(s)) {
        return;
    }
    ind[s] = nc++;
}

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret = mul(ret, x);
        }
        x = mul(x, x), y >>= 1;
    }
    return ret;
}

int dvd(int x, int y) {
    return mul(x, exp(y, mod - 2));
}

void gauss(vector<vector<int>> & aug) {
    if(aug.empty()) {
        return;
    }
    int n = aug[0].size() - 1, m = aug.size(), lst = -1;
    for(int row = 0, col = 0; (row < m && col < n); col++) {
        int tmp = row;
        while(tmp < m && aug[tmp][col] == 0) {
            ++tmp;
        }
        if(tmp == m) {
            continue;
        }
        for(int i = 0; i <= n; i++) {
            swap(aug[row][i], aug[tmp][i]);
        }
        for(int i = n; i >= col; i--) {
            aug[row][i] = dvd(aug[row][i], aug[row][col]);
        }
        for(int i = row + 1; i < m; i++) {
            if(aug[i][col] != 0) {
                for(int j = n; j >= col; j--) {
                    aug[i][j] = (aug[i][j] - mul(aug[i][col], aug[row][j]) + mod) % mod;
                }
            }
        }
        lst = row++;
    }
    for(int i = lst, ind = 0; i >= 0; i--, ind = 0) {
        while(ind < n && aug[i][ind] == 0) {
            ++ind;
        }
        for(int j = i - 1; j >= 0; j--) {
            if(aug[j][ind] != 0) {
                for(int k = n; k >= ind; k--) {
                    aug[j][k] = (aug[j][k] - mul(aug[j][ind], aug[i][k]) + mod) % mod;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    cin.ignore();
    for(int i = 0; i < n; i++) {
        string eq;
        getline(cin, eq);
        int len = eq.length();
        vector<int> spc;
        spc.push_back(-1);
        for(int j = 0; j < len; j++) {
            if(eq[j] == ' ') {
                spc.push_back(j);
            }
        }
        spc.push_back(len);
        for(int j = 0; j < spc.size() - 1; j++) {
            tokens[i].push_back(eq.substr(spc[j] + 1, spc[j + 1] - spc[j] - 1));
        }
        for(string s: tokens[i]) {
            if(s != "1" && s != "=" && s != "*" && s != "/") {
                ins(s);
            }
        }
    }
    vector<vector<int>> eq(n, vector<int>(nc + 1, 0));
    for(int i = 0; i < n; i++) {
        int sgn = 1, cur = 1;
        for(string s: tokens[i]) {
            if(s == "=") {
                sgn *= -1;
            } else if(s == "*") {
                cur = 1;
            } else if(s == "/") {
                cur = -1;
            } else if(s != "1") {
                eq[i][ind[s]] += sgn * cur;
            }
        }
        for(int j = 0; j < nc; j++) {
            eq[i][j] = (eq[i][j] + mod) % mod;
        }
    }
    gauss(eq);
    bool valid = true;
    for(int i = 0; i < n; i++) {
        int tot = 0;
        for(int j = 0; j < nc; j++) {
            tot += (eq[i][j] != 0);
        }
        valid &= (tot != 1);
    }
    cout << (valid ? "valid\n" : "invalid\n");
}