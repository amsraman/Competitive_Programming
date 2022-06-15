#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), cts(100001, 0), p2(n + 1);
    p2[0] = 1;
    for(int i = 1; i <= n; i++) {
        p2[i] = (2 * p2[i - 1]) % mod;
    }
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        for(int j = 1; j * j <= a[i]; j++) {
            if(a[i] % j == 0) {
                ++cts[j];
                if(j != a[i] / j) {
                    ++cts[a[i] / j];
                }
            }
        }
    }
    for(int i = 1e5; i > 0; i--) {
        cts[i] = (p2[cts[i]] + mod - 1) % mod;
        for(int j = 2 * i; j <= 1e5; j += i) {
            cts[i] = (cts[i] - cts[j] + mod) % mod;
        }
    }
    cout << cts[1] << endl;
}