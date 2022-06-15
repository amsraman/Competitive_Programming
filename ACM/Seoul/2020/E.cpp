#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> d(n);
    for(int i = 0; i < n; i++) {
        cin >> d[i];
    }
    vector<vector<bool>> dp(n + 1, vector<bool>(4, false));
    for(int i = 0; i < 4; i++) {
        dp[0][i] = true;
    }
    for(int i = 0; i < n; i++) {
        int lim = ((i == 0 || i == n - 1) ? 2 : 3);
        for(int j = 0; j < lim; j++) {
            for(int k = 0; k < lim; k++) {
                if(abs(j - k) == d[i]) {
                    vector<pair<int, int>> v1, v2;
                    if(j == 0 || j == lim - 1) {
                        v1.push_back({(j == lim - 1) ^ 1, j == lim - 1});
                    } else {
                        v1.push_back({0, 0}), v1.push_back({1, 1});
                    }
                    if(k == 0 || k == lim - 1) {
                        v2.push_back({(k == lim - 1) ^ 1, k == lim - 1});
                    } else {
                        v2.push_back({0, 0}), v2.push_back({1, 1});
                    }
                    for(pair<int, int> x : v1) {
                        for(pair<int, int> y: v2) {
                            dp[i + 1][(x.s << 1) | y.s] = (dp[i + 1][(x.s << 1) | y.s] | dp[i][(x.f << 1) | y.f]);
                        }
                    }
                }
            }
        }
    }
    bool ans = false;
    for(int i = 0; i < 4; i++) {
        ans |= dp[n][i];
    }
    cout << (ans ? "YES" : "NO") << '\n';
}