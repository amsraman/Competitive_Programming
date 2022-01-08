template<class B>
struct SegTree : public B {
    using T = typename B::T;

    size_t n;
    vector<T> seg;

    SegTree(size_t n): n(n), seg(2 * n, B::e) {};

    T qry(int lo, int hi) {
        T ret1 = B::e, ret2 = B::e;
        for(lo += n, hi += n; lo <= hi; lo >>= 1, hi >>= 1) {
            if(lo & 1) {
                ret1 = B::comb(ret1, seg[lo++]);
            }
            if(hi & 1 ^ 1) {
                ret2 = B::comb(seg[hi--], ret2);
            }
        }
        return B::comb(ret1, ret2);
    }

    void upd(int ind, T val) {
        seg[ind += n] = val;
        while(ind > 1) {
            ind >>= 1;
            seg[ind] = B::comb(seg[2 * ind], seg[2 * ind + 1]);
        }
    }
};

// Sample MixIn

struct MaxInt {
    using T = int;
    const T e = 0;

    T comb(T a, T b) {
        return max(a, b);
    }
};
