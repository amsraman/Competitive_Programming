#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template<class B>
struct SparseTable : public B {
    using T = typename B::T;

    int n;
    vector<vector<T>> st;

    SparseTable(int n, vector<T> & a): n(n), st(n, vector<T>(__lg(n) + 1, B::e)) {
        for(int i = 0; i < n; i++) {
            st[i][0] = a[i];
        }
        int lev = __lg(n);
        for(int i = 1; i <= lev; i++) {
            for(int j = 0; j < n; j++) {
                st[j][i] = B::comb(st[j][i - 1], st[min(n - 1, j + (1 << (i - 1)))][i - 1]);
            }
        }
    }

    T qry(int l, int r) {
        int lev = __lg(r - l + 1);
        return B::comb(st[l][lev], st[r - (1 << lev) + 1][lev]);
    }
};

struct Mx {
    using T = ll;
    const T e = LONG_MIN;

    T comb(T a, T b) {
        return max(a, b);
    }
};

struct Mn {
    using T = ll;
    const T e = LONG_MIN;

    T comb(T a, T b) {
        return min(a, b);
    }
};

int n, q, a[100000], b[100000];

int main() {
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> pf(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        pf[i + 1] = pf[i] + b[i] - a[i];
    }
    SparseTable<Mn> mn(n + 1, pf);
    SparseTable<Mx> mx(n + 1, pf);
    for(int i = 0, l, r; i < q; i++) {
        cin >> l >> r;
        ll mn_pf = mn.qry(l, r) - pf[l - 1], mx_pf = mx.qry(l, r) - pf[l - 1];
        if(pf[l - 1] != pf[r] || mn_pf != 0) {
            cout << -1 << '\n';
        } else {
            cout << mx_pf << '\n';
        }
    }
}