#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 1e9 + 7;

int n, m, l, r, bl[100001], dp[100000], bit[100001], aug[500][501];
bool blocked[100000];

int mul(int x, int y) {
    return ((ll) x * y) % mod;
}

int exp(int x, int y) {
    int ret = 1;
    while(y) {
        if(y&1) {
            ret = mul(ret,x);
        }
        x = mul(x,x), y >>= 1;
    }
    return ret;
}

int num_blocked(int x, int y) {
    return bl[min(n,y+1)] - bl[min(n,x)];
}

void point_upd(int k, int val) {
    for(k++; k <= (n+1); k += (k & -k)) {
        bit[k-1] = (bit[k-1] + val) % mod;
    }
}

void range_upd(int x, int y, int val) {
    point_upd(min(n,y+1), mod - val);
    point_upd(min(n,x), val);
}

int qry(int k) {
    int ret = 0;
    for(k++; k>0; k -= (k & -k)) {
        ret = (ret + bit[k-1]) % mod;
    }
    return ret;
}

void gauss()
{
    int lst;
    for(int row = 0, col = 0; (row<=n&&col<n); col++)
    {
        int tmp = row;
        while(tmp<n&&aug[tmp][col]==0)
            ++tmp;
        if(tmp==n)
            continue;
        for(int j = 0; j<=n; j++)
            swap(aug[row][j],aug[tmp][j]);
        for(int j = n; j>=col; j--)
            aug[row][j] = mul(aug[row][j],exp(aug[row][col],mod-2));
        for(int j = row+1; j<n; j++)
            if(aug[j][col]!=0)
                for(int k = n; k>=col; k--)
                    aug[j][k] = (aug[j][k]-mul(aug[j][col],aug[row][k])+mod)%mod;
        lst = row++;
    }
    for(int i = lst, ind = 0; i>=0; i--, ind = 0)
    {
        while(ind<n&&aug[i][ind]==0)
            ++ind;
        for(int j = i-1; j>=0; j--)
            if(aug[j][ind]!=0)
                for(int k = n; k>=ind; k--)
                    aug[j][k] = (aug[j][k]-mul(aug[j][ind],aug[i][k])+mod)%mod;
    }
}

int main() {
    cin >> n >> m >> l >> r;
    for(int i = 0, j; i<m; i++) {
        cin >> j;
        blocked[j-1] = true;
        bl[j] = 1;
    }
    for(int i = 1; i<=n; i++) {
        bl[i] += bl[i-1];
    }
    if(l < 0) {
        // TC 10
        aug[n-1][n-1] = aug[n-1][n] = 1;
        for(int i = 0; i < n - 1; i++) {
            if(!blocked[i]) {
                int num = 0;
                for(int j = i + l; j <= i + r; j++) {
                    if(j < 0 || j >= n || !blocked[j]) {
                        ++num;
                    }
                }
                int inv = exp(num, mod - 2);
                for(int j = i + l; j <= i + r; j++) {
                    if(j >= 0 && j < n && !blocked[j]) {
                        aug[i][j] = (mod - inv) % mod;
                    }
                }
                aug[i][i] = (aug[i][i] + 1) % mod;
            }
        }
        gauss();
        cout << aug[0][n] << endl;
    } else {
        range_upd(0,0,1);
        l = max(l, 1);
        for(int i = 0; i<n; i++) {
            if(!blocked[i]) {
                dp[i] = qry(i);
                int inv = exp(r - l + 1 - num_blocked(i + l, i + r), mod - 2);
                int num_add = mul(dp[i], inv);
                range_upd(i + l, i + r, num_add);
            }
        }
        cout << dp[n-1] << endl;
    }
}