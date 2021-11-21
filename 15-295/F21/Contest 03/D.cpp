#include <bits/stdc++.h>

using namespace std;

template<class B>
struct SegTree : public B {
    using T = typename B::T;

    size_t n;
    vector<T> seg;

    SegTree(size_t n): n(n), seg(2 * n, B::e) {};

    T qry(int lo, int hi) {
        T ret = B::e;
        for(lo += n, hi += n; lo <= hi; lo >>= 1, hi >>= 1) {
            if(lo & 1) {
                ret = B::comb(ret, seg[lo++]);
            }
            if(hi & 1 ^ 1) {
                ret = B::comb(ret, seg[hi--]);
            }
        }
        return ret;
    }

    void upd(int ind, T val) {
        seg[ind += n] = val;
        while(ind > 1) {
            ind >>= 1;
            seg[ind] = B::comb(seg[2 * ind], seg[2 * ind + 1]);
        }
    }
};

struct MaxInt {
    using T = int;
    const T e = 0;

    T comb(T a, T b) {
        return max(a, b);
    }
};

struct MinInt {
    using T = int;
    const T e = 0x3f3f3f3f;

    T comb(T a, T b) {
        return min(a, b);
    }
};

int n, a[300000], ans[300000];
SegTree<MaxInt> mxst((1 << 19));
SegTree<MinInt> mnst((1 << 19));

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i + n] = a[i + 2 * n] = a[i];
    }
    int mx = a[0], mn = a[0];
    for(int i = 0; i < 3 * n; i++) {
        mx = max(mx, a[i]);
        mn = min(mn, a[i]);
    }
    if(2 * mn >= mx) {
        for(int i = 0; i < n; i++) {
            cout << -1 << " ";
        }
        cout << endl;
    } else {
        for(int i = 0; i < 3 * n; i++) {
            mxst.upd(i, a[i]);
            mnst.upd(i, a[i]);
        }
        for(int i = 2 * n - 1; i >= 0; i--) {
            int lb = i, ub = 3 * n - 1;
            while(lb < ub) {
                int mid = (lb + ub) / 2;
                if(mxst.qry(i, mid) > a[i]) {
                    ub = mid;
                } else {
                    lb = mid + 1;
                }
            }
            int big = ub;
            lb = i, ub = 3 * n - 1;
            while(lb < ub) {
                int mid = (lb + ub) / 2;
                if(mnst.qry(i, mid) * 2 < a[i]) {
                    ub = mid;
                } else {
                    lb = mid + 1;
                }
            }
            if(ub < big) {
                ans[i] = ub - i;
            } else {
                ans[i] = big - i + ans[big];
            }
        }
        for(int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
}