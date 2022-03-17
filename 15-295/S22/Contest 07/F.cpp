#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int w, n, m, a[30000], num[531441], op[2][256];
string gate, ops = "AaOoXx";

int conv(int x) {
    if(x == 0) {
        return 0;
    }
    return 3 * conv(x / 2) + x % 2;
}

int app(int f, int s, char g) {
    int sgn = 0;
    if(g <= 'z' && g >= 'a') {
        g += 'A' - 'a';
        sgn = 1;
    }
    if(g == 'A') {
        return (f & s) ^ sgn;
    } else if(g == 'O') {
        return (f | s) ^ sgn;
    }
    return (f ^ s) ^ sgn;
}

int get_op(int f, char g) {
    int ct = 0, lst = -1;
    for(int i = 0; i < 2; i++) {
        if(app(f, i, g) == 0) {
            ++ct, lst = i;
        }
    }
    if(ct == 2) {
        return 2;
    }
    return lst;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> w >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ++num[conv(a[i])];
    }
    int pw = 1;
    for(int i = 0; i < w; i++) {
        pw *= 3;
    }
    for(int i = 0; i < pw; i++) {
        int cur = i, pos = 1;
        while(cur > 0 && cur % 3 != 2) {
            cur /= 3, pos *= 3;
        }
        if(cur > 0) {
            num[i] = num[i - pos] + num[i - 2 * pos];
        }
    }
    for(int i = 0; i < 2; i++) {
        for(char c: ops) {
            op[i][c] = get_op(i, c);
        }
    }
    ll ans = 0;
    for(int i = 0; i < m; i++) {
        cin >> gate;
        ll ans = 0;
        for(int j = 0; j < (1 << w); j++) {
            int msk1 = 0, msk2 = 0;
            bool fail = false;
            for(int k = 0; k < w; k++) {
                int cur = (j >> k) & 1;
                if(op[cur][gate[k]] == -1) {
                    fail = true;
                }
                msk1 = 3 * msk1 + cur;
                msk2 = 3 * msk2 + op[cur][gate[k]];
            }
            if(!fail) {
                ans += 1LL * num[msk1] * num[msk2];
            }
        }
        cout << ans << '\n';
    }
}