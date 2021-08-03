#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 1e18;

int n, m;
ll k, ncr[51][51], dp[51][51];
bool used[50];
vector<int> ans;

ll overflow_mul(ll a, ll b) {
    if(b == 0) {
        return 0;
    }
    if(a > (INF + b - 1) / b) {
        return INF;
    }
    return a * b;
}

int main() {
    cin >> n >> m >> k;
    ncr[0][0] = dp[0][0] = 1;
    for(int i = 1; i<=n; i++) {
        ncr[i][0] = 1;
        for(int j = 1; j<=i; j++) {
            ncr[i][j] = min(INF, ncr[i-1][j-1] + ncr[i-1][j]);
        }
    }
    for(int i = 0; i<=n; i++) {
        if(i > 0) {
            dp[i][0] = min(INF, overflow_mul(i - 1, min(INF, dp[i-1][0] + dp[i-2][0])));
        }
        for(int j = 1; j<=n; j++) {
            dp[i][j] = overflow_mul(dp[i][j-1], i + j);
            if(i > 0) {
                dp[i][j] = min(INF, dp[i][j] + overflow_mul(dp[i-1][j-1], i));
            }
        }
    }
    set<int> remaining;
    for(int i = 0; i<n; i++) {
        remaining.insert(i);
    }
    for(int i = 0, free = 0; i<n; i++) {
        for(int j: remaining) {
            int nxt_m = m, nxt_free = 2 * free;
            if(j == i) {
                --nxt_m;
            } else {
                nxt_free += (j > i ? 1 : -1);
                nxt_free += (used[i] ? -1 : 1);
            }
            nxt_free /= 2;
            ll num_left = (nxt_m + nxt_free <= n - i - 1 ? overflow_mul(ncr[n-i-nxt_free-1][nxt_m], dp[n-nxt_m-nxt_free-i-1][nxt_free]) : 0);
            if(num_left >= k) {
                m = nxt_m;
                free = nxt_free;
                remaining.erase(j);
                used[j] = true;
                ans.push_back(j+1);
                break;
            } else {
                k -= num_left;
            }
        }
    }
    if(ans.size() != n) {
        cout << -1 << endl;
    } else {
        for(int i: ans) {
            cout << i << " ";
        }
        cout << endl;
    }
}