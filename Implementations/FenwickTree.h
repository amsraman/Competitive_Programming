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