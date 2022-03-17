#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int n, lens[11], places[11][11], sums[20];
string a[100000];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        int len = a[i].length();
        for(int j = 0; j < len; j++) {
            places[len][j] += (a[i][len - j - 1] - '0');
        }
        ++lens[len];
    }
    int ans = 0;
    for(int i = 1; i <= 10; i++) {
        for(int j = 1; j <= 10; j++) {
            for(int i1 = 0, i2 = 0, k = 0; (i1 < i || i2 < j); i1++, i2++) {
                if(i1 < i) {
                    sums[k] = (sums[k] + (1LL * lens[j] * places[i][i1])) % mod;
                    k++;
                }
                if(i2 < j) {
                    sums[k] = (sums[k] + (1LL * lens[i] * places[j][i2])) % mod;
                    k++;
                }
            }
        }
    }
    int p10 = 1;
    for(int i = 0; i < 20; i++) {
        ans = (ans + (1LL * p10 * sums[i]) % mod) % mod;
        p10 = (1LL * p10 * 10) % mod;
    }
    cout << ans << endl;
}