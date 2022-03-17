int mul(int x, int y) {
    return (1LL * x * y) % mod;
}

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) {
            ret = mul(ret, x);
        }
        x = mul(x, x), y >>= 1;
    }
    return ret;
}

int dvd(int x, int y) {
    return mul(x, exp(y, mod - 2));
}

void gauss(vector<vector<int>> & aug) {
    if(aug.empty()) {
        return;
    }
    int n = aug[0].size() - 1, m = aug.size(), lst = -1;
    for(int row = 0, col = 0; (row < m && col < n); col++) {
        int tmp = row;
        while(tmp < m && aug[tmp][col] == 0) {
            ++tmp;
        }
        if(tmp == m) {
            continue;
        }
        for(int i = 0; i <= n; i++) {
            swap(aug[row][i], aug[tmp][i]);
        }
        for(int i = n; i >= col; i--) {
            aug[row][i] = dvd(aug[row][i], aug[row][col]);
        }
        for(int i = row + 1; i < m; i++) {
            if(aug[i][col] != 0) {
                for(int j = n; j >= col; j--) {
                    aug[i][j] = (aug[i][j] - mul(aug[i][col], aug[row][j]) + mod) % mod;
                }
            }
        }
        lst = row++;
    }
    for(int i = lst, ind = 0; i >= 0; i--, ind = 0) {
        while(ind < n && aug[i][ind] == 0) {
            ++ind;
        }
        for(int j = i - 1; j >= 0; j--) {
            if(aug[j][ind] != 0) {
                for(int k = n; k >= ind; k--) {
                    aug[j][k] = (aug[j][k] - mul(aug[j][ind], aug[i][k]) + mod) % mod;
                }
            }
        }
    }
}