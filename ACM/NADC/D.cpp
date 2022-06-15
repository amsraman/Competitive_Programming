#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int mod = 998244353;

template<typename T>
struct FenwickTree {
    size_t n;
    vector<T> bit;

    FenwickTree(size_t n): n(n), bit(n, 0) {};

    FenwickTree(int n, vector<T> & init): n(n), bit(n) {
        copy(init.begin(), init.end(), bit.begin());
        for(int i = 1; i <= n; i++) {
            if(i + (i & -i) <= n) {
                bit[i + (i & -i) - 1] = (bit[i + (i & -i) - 1] + bit[i - 1]) % mod;
            }
        }
    }

    T qry(int k) {
        T ret = 0;
        for(k++; k > 0; k -= (k & -k)) {
            ret = (ret + bit[k - 1]) % mod;
        }
        return ret;
    }

    T range_qry(int l, int r) {
        return (qry(r) - qry(l - 1) + mod) % mod;
    }

    void upd(int k, T x) {
        for(k++; k <= n; k += (k & -k)) {
            bit[k - 1] = (bit[k - 1] + x) % mod;
        }
    }
};

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

struct Info {
    using T = ll;
    const T e = (1LL << 60) - 1;

    T comb(T a, T b) {
        return (a & b);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll msk = (1LL << 60) - 1;
    vector<pair<int, int>> inds;
    for(int i = 0, j = 0; i < n; i++) {
        msk &= (a[(n - i) % n]), j++;
        ll nm = (msk & a[(n - i - 1) % n]);
        if(nm != msk || i == n - 1) {
            inds.push_back({i - j + 1, j}), j = 0;
        }
    }
    if(msk == 0) {
        inds.pop_back();
    }
    ll ans = 0;
    for(pair<int, int> i: inds) {
        vector<ll> shifted_vals;
        for(int j = i.f; j > 0; j--) {
            shifted_vals.push_back(a[n - j]);
        }
        for(int j = 0; shifted_vals.size() < n; j++) {
            shifted_vals.push_back(a[j]);
        }
        SparseTable<Info> st(n, shifted_vals);
        FenwickTree<int> ft(n + 1);
        vector<int> nearest_and(n, 0);
        for(int j = 1; j < n; j++) {
            nearest_and[j] = nearest_and[j - 1];
            while(st.qry(nearest_and[j], j) == 0) {
                ++nearest_and[j];
            }
        }
        ft.upd(0, 1);
        for(int j = i.f; j < n; j++) {
            ft.upd(j + 1, ft.range_qry(nearest_and[j], j));
        }
        ans = (ans + ft.range_qry(n - i.s + 1, n)) % mod;
    }
    if(msk > 0) {
        ans = (ans - n + 1 + mod) % mod;
    }
    cout << ans << '\n';
}