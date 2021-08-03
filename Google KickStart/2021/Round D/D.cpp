#include <bits/stdc++.h>
typedef long long ll;
#define int long long

using namespace std;

int t, n, q, p;
ll a[500000];

template<typename T>
struct FenwickTree {
    size_t n;
    vector<T> amt, bit;

    FenwickTree(size_t n): n(n), amt(n, 0), bit(n, 0) {};

    T qry(int k) {
        T ret = 0;
        for(k++; k > 0; k -= (k & (-k))) {
            ret += bit[k - 1];
        }
        return ret;
    }

    T range_qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }

    void upd(int k, T x) {
        T diff = x - amt[k];
        amt[k] += diff;
        for(k++; k <= n; k += (k & (-k))) {
            bit[k - 1] += diff;
        }
    }
};

int v_p(ll x) {
    if(x == 0) {
        return 0;
    }
    int ret = 0;
    while(x % p == 0) {
        x /= p, ++ret;
    }
    return ret;
}

signed main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> q >> p;
        FenwickTree<ll> bit1(n), bit2(n), bit3(n), bit4(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            if(a[i] % p != 0 && a[i] >= p) {
                bit1.upd(i, v_p(a[i] - (a[i] % p)));
                bit2.upd(i, v_p(a[i] + (a[i] % p)) - 1);
                bit4.upd(i, 1);
            } else if(a[i] >= p) {
                bit3.upd(i, v_p(a[i]));
            }
        }
        cout << "Case #" << _ << ": ";
        for(int i = 0; i < q; i++) {
            int type;
            cin >> type;
            if(type == 1) {
                int pos;
                ll val;
                cin >> pos >> val;
                if(a[pos - 1] % p == 0 && a[pos - 1] >= p) {
                    bit3.upd(pos - 1, 0);
                } else if(a[pos - 1] >= p) {
                    bit1.upd(pos - 1, 0);
                    bit2.upd(pos - 1, 0);
                    bit4.upd(pos - 1, 0);
                }
                if(val % p == 0 && val >= p) {
                    bit3.upd(pos - 1, v_p(val));
                } else if(val >= p) {
                    bit1.upd(pos - 1, v_p(val - (val % p)));
                    bit2.upd(pos - 1, v_p(val + (val % p)) - 1);
                    bit4.upd(pos - 1, 1);
                }
                a[pos - 1] = val;
            } else {
                int s, l, r;
                cin >> s >> l >> r;
                int ans = v_p(s) * bit4.range_qry(l - 1, r - 1) + bit1.range_qry(l - 1, r - 1) + s * bit3.range_qry(l - 1, r - 1);
                if(p == 2 && (s % 2 == 0)) {
                    ans += bit2.range_qry(l - 1, r - 1);
                }
                cout << ans << " ";
            }
        }
        cout << endl;
    }
}