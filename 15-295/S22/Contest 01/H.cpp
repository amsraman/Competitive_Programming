#include <bits/stdc++.h>

using namespace std;

int t, n;
bool bad[500001];
string s;
vector<int> ans;

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
    // convolves a and b into a
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
        a[i] = round(a[i].real());
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> s;
        for(int i = 1; i <= n; i++) {
            bad[i] = 0;
        }
        vector<cd> pa(n + 1, 0), pb(n + 1, 0);
        // Find absolute value of all numbers that can be written as j - i
        // Where s[j] = 'V' and s[i] = 'K'
        // Offset by n
        for(int i = 0; i < n; i++) {
            if(s[i] == 'V') {
                pa[i + 1] = 1;
            } else if(s[i] == 'K') {
                pb[n - i - 1] = 1;
            }
        }
        fft_conv(pa, pb);
        for(int i = 0; i < pa.size(); i++) {
            if(pa[i].real() > 0) {
                bad[abs(i - n)] = true;
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 2 * i; j <= n; j += i) {
                bad[i] |= bad[j];
            }
            if(bad[i] == 0) {
                ans.push_back(i);
            }
        }
        cout << ans.size() << '\n';
        for(int i: ans) {
            cout << i << " ";
        }
        cout << '\n';
        ans.clear();
    }
}