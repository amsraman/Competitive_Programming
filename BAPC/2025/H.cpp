#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q; cin >> q;
    while(q--) {
        int n, x; string s; cin >> n >> x >> s;
        auto get_par = [&](int u) {
            if(u <= 1) return -1;
            int step = 1 << __lg(u);
            while(u >= step) u -= step / 2;
            return u;
        };
        auto proc = [&](auto rec, int u, int lev) -> int {
            if(lev == (int) s.length()) return u;
            char go = s[lev];
            if(go == 'U') {
                if(u == 1) return -1;
                return rec(rec, get_par(u), lev + 1);
            }
            int step = 1 << __lg(u);
            int sz = 1 + (n - u) / step;
            if((sz - 1) % 2 == 0) {
                go ^= 'L' ^ 'R';
            }
            if(go == 'L') {
                int ch = u + step;
                return ch <= n ? rec(rec, ch, lev + 1) : -1;
            } else {
                int ch = u + 2 * step;
                return ch <= n ? rec(rec, ch, lev + 1) : -1;
            }
        };
        cout << proc(proc, x, 0) << '\n';
    }
}
/*
main tree: 1, 2, 3, ..

st1: 3, 5, ...
st2: 2, 4, 6, ...

st11: 7, 11, 15, ...
st12: 5, 9, 13, ...

st111: 15, 23, 31, ...
st112: 11, 19, 27, ...

step 1: 1
step 2: 2 3
step 4: 4 5 6 7
...
*/