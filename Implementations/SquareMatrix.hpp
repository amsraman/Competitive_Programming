template <typename T, int N> // templated square matrix
struct Matrix : array<array<T, N>, N> {
    Matrix() {
        for(int i = 0; i < N; i++) {
            (*this)[i].fill(0);
        }
    }
    Matrix id() {
        Matrix res;
        for(int i = 0; i < N; i++) res[i][i] = 1;
        return res;
    }
    vector<T> operator*(const vector<T> & vec) {
        assert(vec.size() == N);
        vector<T> res(N, 0);
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                res[i] += (*this)[i][j] * vec[j];
            }
        }
        return res;
    }
    Matrix operator*(const Matrix & mat) {
        Matrix res;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                for(int k = 0; k < N; k++) {
                    res[i][j] += (*this)[i][k] * mat[k][j];
                }
            }
        }
        return res;
    }
    void operator*=(const vector<T> & vec) {*this = *this * vec;}
    void operator*=(const Matrix & mat) {*this = *this * mat;}
    Matrix operator^(long long val) {
        assert(val >= 0);
        Matrix res = id(), multiplier = *this;
        while(val) {
            if(val & 1) res *= multiplier;
            multiplier *= multiplier, val >>= 1;
        }
        return res;
    }
    void operator^=(long long val) {*this = *this ^ val;}
};