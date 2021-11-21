#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

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

int n, q, a[200000];
set<pair<int, int>> alt;

ll choose2(int x) {
    return 1LL * x * (x - 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    FenwickTree<ll> seq(n);
    auto add = [&] (pair<int, int> in) {
        alt.insert(in);
        seq.upd(in.s, choose2(in.s - in.f + 2));
    };
    auto rem = [&] (pair<int, int> in) {
        alt.erase(in);
        seq.upd(in.s, -choose2(in.s - in.f + 2));
    };
    int cur = 0;
    for(int i = 0; i < n; i++) {
        if(i == n - 1 || a[i] == a[i + 1]) {
            add({cur, i});
            cur = i + 1;
        }
    }
    alt.insert({n, n});
    for(int i = 0, t, l, r; i < q; i++) {
        cin >> t >> l >> r;
        --l, --r;
        if(t == 1) {
            auto lb = alt.lower_bound({l, -1}), ub = alt.lower_bound({r + 1, -1});
            if(lb->f != 0 && lb->f == l) {
                pair<int, int> in1 = *lb, in2 = *(--lb);
                rem(in1), rem(in2);
                add({in2.f, in1.s});
            } else if(l != 0) {
                pair<int, int> in = *(--lb);
                rem(in);
                add({in.f, l - 1}), add({l, in.s});
            }
            if(ub->f != n && ub->f == r + 1) {
                pair<int, int> in1 = *ub, in2 = *(--ub);
                rem(in1), rem(in2);
                add({in2.f, in1.s});
            } else if(r != n - 1) {
                pair<int, int> in = *(--ub);
                rem(in);
                add({in.f, r}), add({r + 1, in.s});
            }
        } else {
            ll ans = 0;
            auto lb = alt.lower_bound({l, -1}), ub = --alt.lower_bound({r + 1, -1});
            if(lb->f > l) {
                --lb;
            }
            if(lb == ub) {
                cout << choose2(r - l + 2) << '\n';
            } else {
                cout << choose2(lb->s - l + 2) + choose2(r - ub->f + 2) + seq.qry(lb->s + 1, ub->f - 1) << '\n';
            }
        }
    }
}