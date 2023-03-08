#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 1e9 + 7;

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
                res[i] = (res[i] + 1LL * (*this)[i][j] * vec[j]) % mod;
            }
        }
        return res;
    }
    Matrix operator*(const Matrix & mat) {
        Matrix res;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                for(int k = 0; k < N; k++) {
                    res[i][j] =  (res[i][j] + 1LL * (*this)[i][k] * mat[k][j]) % mod;
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

int main() {
    ll n; int b, ans = 0; cin >> n >> b;
    if(n <= 2) {
        if(n == 1) cout << (1 <= b && b < 10) << '\n';
        if(n == 2) cout << (10 <= b && b < 100) << '\n';
        return 0;
    }
    Matrix<int, 90> mat;
    for(int lst = 0; lst < 10; lst++) {
        for(int sum = 0; sum < 9; sum++) {
            for(int nxt = 0; nxt < 10; nxt++) if(nxt != lst) {
                ++mat[9 * nxt + (sum + nxt) % 9][9 * lst + sum];
            }
        }
    }
    vector<int> init(90, 0);
    for(int i = 1; i < 10; i++) ++init[9 * i + i % 9];
    init = (mat ^ (n - 3)) * init;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) if(i != j) {
            int lst = 10 * i + j, md = (b % 9 - lst % 9 + 9) % 9;
            if(lst % 25 != b % 25) continue;
            for(int pv = 0; pv < 10; pv++) if(pv != i) {
                ans = (ans + init[9 * pv + md]) % mod;
            }
        }
    }
    cout << ans << '\n';
}