// What a silly problem.
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define f first
#define s second

using namespace std;

const ll INF = 1e18;

int n, a[50], b[50];
ll dp[50][51][51];
pair<int, int> ord[50];

bool ok(ld ratio) {
    vector<ll> val(n);
    ll ret = -INF;
    for(int i = 0; i < n; i++) {
        val[i] = (ll) (ratio * b[i] - (ld) a[i] * 1000);
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k <= n; k++) {
                dp[i][j][k] = -INF;
            }
        }
    }
    dp[0][0][1] = val[0];
    for(int i = 0; i < n - 1 ; i++) {
        for(int j = 0; j <= i + 1; j++) {
            for(int k = 0; j + k <= i + 1; k++) {
                int num_under = i + 1 - j - k;
                if(a[i] == a[i + 1]) {
                    if(num_under < j) {
                        dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k]);
                    }
                    dp[i + 1][j][k + 1] = max(dp[i + 1][j][k + 1], dp[i][j][k] + val[i + 1]);
                } else {
                    if(num_under < j + k) {
                        dp[i + 1][j + k][0] = max(dp[i + 1][j + k][0], dp[i][j][k]);
                    }
                    dp[i + 1][j + k][1] = max(dp[i + 1][j + k][1], dp[i][j][k] + val[i + 1]);
                }
            }
        }
    }
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            ret = max(ret, dp[n - 1][i][j]);
        }
    }
    return ret >= 0;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ord[i].f = a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        ord[i].s = b[i];
    }
    sort(ord, ord + n);
    reverse(ord, ord + n);
    for(int i = 0; i < n; i++) {
        a[i] = ord[i].f, b[i] = ord[i].s;
    }
    ld lb = 0, ub = 1e11;
    for(int i = 0; i < 200; i++) {
        ld mid = (lb + ub) / 2;
        if(ok(mid)) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    if(ok((ll) ub)) {
        cout << (ll) ub << endl;
    } else {
        cout << (ll) (ub + 1.0) << endl;
    }
}