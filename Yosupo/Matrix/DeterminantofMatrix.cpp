#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret = (1LL * ret * x) % mod;
        }
        x = (1LL * x * x) % mod, y >>= 1;
    }
    return ret;
}

template <typename T>
T determinant(vector<vector<T>> mat) {
    assert(mat.size() == mat[0].size());
    int n = mat.size(); T det = 1;
    for(int i = 0; i < n; i++) {
        int piv = i;
        while(piv < n - 1 && mat[piv][i] == 0) ++piv;
        swap(mat[i], mat[piv]);
        if(mat[i][i] == 0) return 0;
        if(i != piv) det = (mod - det) % mod;
        det = (1LL * det * mat[i][i]) % mod;
        for(int j = i + 1; j < n; j++) {
            mat[i][j] = (1LL * mat[i][j] * exp(mat[i][i], mod - 2)) % mod;
        }
        for(int j = 0; j < n; j++) {
            if(j != i && mat[j][i] != 0) {
                for(int k = i + 1; k < n; k++) {
                    mat[j][k] = (mat[j][k] - (1LL * mat[i][k] * mat[j][i]) % mod + mod) % mod;
                }
            }
        }
    }
    return det;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> mat(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    cout << determinant(mat) << '\n';
}