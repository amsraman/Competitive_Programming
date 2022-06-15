// 163 ms
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template<typename T>
struct FenwickTree {
    size_t n;
    vector<T> bit;

    FenwickTree(size_t n): n(n), bit(n, 0) {};

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
        for(k++; k <= n; k += (k & (-k))) {
            bit[k - 1] += x;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    FenwickTree<ll> ft(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ft.upd(i, a[i]);
    }
    while(q--) {
        int type;
        cin >> type;
        if(type == 0) {
            int p, x;
            cin >> p >> x;
            ft.upd(p, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << ft.range_qry(l, r - 1) << '\n';
        }
    }
}