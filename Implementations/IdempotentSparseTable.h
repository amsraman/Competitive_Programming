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
    using T = int;
    const T e = INT_MAX;

    T comb(T a, T b) {
        return min(a, b);
    }
};