template <class B>
struct SparseTable : public B {
    using T = typename B::T;
    int n; vector<vector<T>> st;
    SparseTable(vector<T> & a): n((int) a.size()), st(__lg(n) + 1, vector<T>(n, B::e)) {
        for(int i = 0; i < n; i++) {
            st[0][i] = a[i];
        }
        int lev = __lg(n);
        for(int i = 1; i <= lev; i++) {
            for(int j = 0; j < n; j++) {
                st[i][j] = B::comb(st[i - 1][j], st[i - 1][min(n - 1, j + (1 << (i - 1)))]);
            }
        }
    }
    T qry(int l, int r) {
        int lev = __lg(r - l + 1);
        return B::comb(st[lev][l], st[lev][r - (1 << lev) + 1]);
    }
};

struct Band {
    using T = int;
    const T e = INT_MAX;
    T comb(T a, T b) {
        return min(a, b);
    }
};