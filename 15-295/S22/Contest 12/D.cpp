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

struct Info {
    using T = ll;
    const T e = 0;

    T comb(T a, T b) {
        return __gcd(a, b);
    }
};

int t, n;
ll a[200000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<ll> b;
        for(int i = 0; i < n - 1; i++) {
            b.push_back(abs(a[i] - a[i + 1]));
        }
        SparseTable<Info> st(n - 1, b);
        int ans = 0;
        for(int i = 0; i < n - 1; i++) {
            int lb = i, ub = n - 2;
            while(lb < ub) {
                int mid = (lb + ub + 1) / 2;
                if(st.qry(i, mid) > 1) {
                    lb = mid;
                } else {
                    ub = mid - 1;
                }
            }
            if(b[i] != 1) {
                ans = max(ans, ub - i + 1);
            }
        }
        cout << ans + 1 << '\n';
    }
}