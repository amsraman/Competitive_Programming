#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template<typename T>
struct FenwickTree {
    int n;
    vector<T> bit;

    FenwickTree(int n): n(n), bit(n, 0) {};

    T qry(int x) {
        T ret = 0;
        for(x++; x > 0; x -= (x & -x)) {
            ret += bit[x - 1];
        }
        return ret;
    }

    T qry(int x, int y) {
        return qry(y) - qry(x - 1);
    }

    void upd(int x, T k) {
        for(x++; x <= n; x += (x & -x)) {
            bit[x - 1] += k;
        }
    }
};

int n, b[200000], rec[200000];
ll ans;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        rec[i] = -1;
    }
    FenwickTree<int> bit(n);
    for(int i = 0; i < n; i++) {
        if(rec[b[i] - 1] != -1) {
            bit.upd(rec[b[i] - 1], -1);
        }
        ans += bit.qry(rec[b[i] - 1], i);
        rec[b[i] - 1] = i;
        bit.upd(i, 1);
    }
    cout << ans << endl;
}