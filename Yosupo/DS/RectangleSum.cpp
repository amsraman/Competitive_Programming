// 305 ms
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <typename T>
struct FenwickTree {
    size_t n;
    vector<T> bit;

    FenwickTree(size_t n): n(n), bit(n, 0) {};

    FenwickTree(int n, vector<T> & init): n(n), bit(n) {
        copy(init.begin(), init.end(), bit.begin());
        for(int i = 1; i <= n; i++) {
            if(i + (i & -i) <= n) {
                bit[i + (i & -i) - 1] += bit[i - 1];
            }
        }
    }

    T qry(int k) {
        T ret = 0;
        for(k++; k > 0; k -= k & -k) {
            ret += bit[k - 1];
        }
        return ret;
    }

    T qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }

    void upd(int k, T x) {
        for(k++; k <= n; k += k & -k) {
            bit[k - 1] += x;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> l(q), r(q), y_coords;
    vector<array<int, 4>> events(n + 2 * q);
    vector<ll> ans(q, 0);
    for(int i = 0; i < n; i++) {
        cin >> events[i][0] >> events[i][2] >> events[i][3];
        events[i][1] = 1, y_coords.push_back(events[i][2]);
    }
    for(int i = 0; i < q; i++) {
        cin >> events[(i << 1) + n][0] >> l[i] >> events[(i << 1 ^ 1) + n][0] >> r[i];
        events[(i << 1) + n][1] = events[(i << 1 ^ 1) + n][1] = 0;
        events[(i << 1) + n][2] = events[(i << 1 ^ 1) + n][2] = i;
        events[(i << 1) + n][3] = -1, events[(i << 1 ^ 1) + n][3] = 1;
    }
    sort(events.begin(), events.end());
    sort(y_coords.begin(), y_coords.end());
    y_coords.erase(unique(y_coords.begin(), y_coords.end()), y_coords.end());
    FenwickTree<ll> ft(y_coords.size());
    for(array<int, 4> e: events) {
        if(e[1]) {
            int ind = lower_bound(y_coords.begin(), y_coords.end(), e[2]) - y_coords.begin();
            ft.upd(ind, e[3]);
        } else {
            int lo_ind = lower_bound(y_coords.begin(), y_coords.end(), l[e[2]]) - y_coords.begin();
            int hi_ind = lower_bound(y_coords.begin(), y_coords.end(), r[e[2]]) - y_coords.begin();
            ans[e[2]] += ft.qry(lo_ind, hi_ind - 1) * e[3];
        }
    }
    for(ll a: ans) {
        cout << a << '\n';
    }
}