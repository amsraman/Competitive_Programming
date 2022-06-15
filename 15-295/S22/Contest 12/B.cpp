#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

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

int t, n, a[200000], ind[200000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n;
        vector<pair<int, int>> ord;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            ord.push_back({a[i], i});
        }
        sort(ord.begin(), ord.end());
        int sz = 0;
        for(int i = 0, j = 0; i < n; i++) {
            if(i > 0 && ord[i].f != ord[i - 1].f) {
                ++sz;
            }
            ind[ord[i].s] = sz;
        }
        FenwickTree<int> ft(sz + 1);
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            ans += min(ft.range_qry(0, ind[i] - 1), ft.range_qry(ind[i] + 1, sz));
            ft.upd(ind[i], 1);
        }
        cout << ans << '\n';
    }
}