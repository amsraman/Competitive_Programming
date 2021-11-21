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
        seg[ind += n] = B::upd(seg[ind], val);
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

    T upd(T a, T b) {
        return b;
    }
};

int t, n, a[500000], dp[500000];
vector<int> events[500000];

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        SegTree<MaxInt> seg((1 << (1 + __lg(n))));
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            dp[i] = 1;
        }
        stack<int> st;
        for(int i = 0; i < n; i++) {
            while(!st.empty() && a[st.top()] < a[i]) {
                st.pop();
            }
            if(!st.empty()) {
                events[st.top()].push_back(i);
            }
            st.push(i);
        }
        for(int i = 0; i < n; i++) {
            for(int j: events[i]) {
                dp[j] = seg.qry(0, a[j] - 1) + 2;
            }
            dp[i] = max(dp[i], seg.qry(0, a[i] - 1) + 1);
            seg.upd(a[i] - 1, dp[i]);
        }
        cout << seg.qry(0, n - 1) << endl;
        for(int i = 0; i < n; i++) {
            events[i].clear();
        }
    }
}