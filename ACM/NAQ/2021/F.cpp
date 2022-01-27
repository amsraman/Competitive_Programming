#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int n, ind[52], ct[10], vc, cc, pr[100001][42][10], sf[100001][42][10], tot[100001], cons[100001][42], vow[100001][10], ans;
string s;

int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

bool is_vow(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int conv(char c) {
    if(c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    return 26 + c - 'A';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> s;
    n = s.length();
    for(char i = 'a'; i <= 'z'; i++) {
        if(is_vow(i)) {
            ind[conv(i)] = vc++;
        } else {
            ind[conv(i)] = cc++;
        }
    }
    for(char i = 'A'; i <= 'Z'; i++) {
        if(is_vow(i)) {
            ind[conv(i)] = vc++;
        } else {
            ind[conv(i)] = cc++;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 42; j++) {
            for(int k = 0; k < 10; k++) {
                pr[i + 1][j][k] = pr[i][j][k];
            }
        }
        if(is_vow(s[i])) {
            ++ct[ind[conv(s[i])]];
        } else {
            for(int j = 0; j < 10; j++) {
                pr[i + 1][ind[conv(s[i])]][j] += ct[j];
            }
        }
    }
    memset(ct, 0, sizeof(ct));
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < 42; j++) {
            for(int k = 0; k < 10; k++) {
                sf[i][j][k] = sf[i + 1][j][k];
            }
        }
        if(is_vow(s[i])) {
            ++ct[ind[conv(s[i])]];
        } else {
            for(int j = 0; j < 10; j++) {
                sf[i][ind[conv(s[i])]][j] += ct[j];
            }
        }
        for(int j = 0; j < 42; j++) {
            for(int k = 0; k < 10; k++) {
                tot[i] += sf[i][j][k];
                vow[i][k] += sf[i][j][k];
                cons[i][j] += sf[i][j][k];
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(is_vow(s[i])) {
            for(int j = 0; j < 42; j++) {
                for(int k = 0; k < 10; k++) {
                    if(k != ind[conv(s[i])]) {
                        int bad = cons[i + 1][j] + vow[i + 1][k] + vow[i + 1][ind[conv(s[i])]] - sf[i + 1][j][k] - sf[i + 1][j][ind[conv(s[i])]];
                        ans = (ans + mul(pr[i][j][k], tot[i + 1] - bad)) % mod;
                    }
                }
            }
        }
    }
    cout << ans << '\n';
}