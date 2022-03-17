#include <bits/stdc++.h>

using namespace std;

typedef complex<double> cd;

const double PI = acos(-1);

void fft(vector<cd> & a, bool inv) {
    int sz = a.size();
    for(int i = 1, j = 0; i < sz; i++) {
        int bit = sz >> 1;
        for(; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if(i < j) {
            swap(a[i], a[j]);
        }
    }
    for(int len = 1; len < sz; len <<= 1) {
        double ang = PI / len * (inv ? 1 : -1);
        cd w(cos(ang), sin(ang));
        for(int i = 0; i < sz; i += (2 * len)) {
            cd wn(1);
            for(int j = i; j < i + len; j++) {
                cd x = a[j], y = a[j + len] * wn;
                a[j] = x + y;
                a[j + len] = x - y;
                wn *= w;
            }
        }
    }
    if(inv) {
        for(int i = 0; i < sz; i++) {
            a[i] /= sz;
        }
    }
}

void fft_conv(vector<cd> & a, vector<cd> & b) {
    int pow = 1, res_sz = a.size() + b.size() - 1;
    while(pow < res_sz) {
        pow <<= 1;
    }
    a.resize(pow), b.resize(pow);
    fft(a, false), fft(b, false);
    for(int i = 0; i < pow; i++) {
        a[i] *= b[i];
    }
    fft(a, true);
    for(int i = 0; i < pow; i++) {
        a[i] = (long long) round(a[i].real());
    }
}

int n, m, k, ln[200000][4], rn[200000][4], rec[4], msk[200000], ans;
string s, t, dna = "ATCG";
bool bad[200000];

int main() {
    cin >> n >> m >> k >> s >> t;
    for(int i = 0; i < 4; i++) {
        rec[i] = -k - 1;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 4; j++) {
            if(s[i] == dna[j]) {
                rec[j] = i;
            }
            ln[i][j] = i - rec[j];
        }
    }
    for(int i = 0; i < 4; i++) {
        rec[i] = n + k + 1;
    }
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < 4; j++) {
            if(s[i] == dna[j]) {
                rec[j] = i;
            }
            rn[i][j] = rec[j] - i;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 4; j++) {
            if(min(ln[i][j], rn[i][j]) <= k) {
                msk[i] |= (1 << j);
            }
        }
    }
    vector<cd> va[4], vb[4];
    for(int i = 0; i < 4; i++) {
        va[i].resize(n, 0.0);
        vb[i].resize(m, 0.0);
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < 4; j++) {
            if(t[i] == dna[j]) {
                vb[j][m - i - 1] = 1.0;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 4; j++) {
            if(!(msk[i] & (1 << j))) {
                va[j][i] = 1.0;
            }
        }
    }
    for(int i = 0; i < 4; i++) {
        fft_conv(va[i], vb[i]);
        for(int j = 0; j < n; j++) {
            if(va[i][j + m - 1] != 0.0) {
                bad[j] = true;
            }
        }
    }
    for(int i = 0; i < n - m + 1; i++) {
        ans += (int) (!bad[i]);
    }
    cout << ans << endl;
}