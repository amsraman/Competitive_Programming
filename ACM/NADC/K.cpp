#include <bits/stdc++.h>
typedef long double ld;
#define f first
#define s second

using namespace std;

const int delta = 27;

int n, k, p[100000], d[100000];
ld p2[delta + 1];
pair<ld, int> dp[100001][2];
// 0 - Not necessarily covered by station
// 1 - Covered by station

pair<ld, int> try_penalty(ld penalty) {
    dp[0][0] = dp[0][1] = {0, 0};
    for(int i = 0; i < n; i++) {
        dp[i + 1][0] = dp[i][0], dp[i + 1][1] = {0, 0};
        ld extra = p[i];
        // Iterate over locations for the previous station
        for(int j = i - 1; j >= 0 && d[i] - d[j] <= delta; j--) {
            extra /= p2[d[j + 1] - d[j]];
            dp[i + 1][0] = max(dp[i + 1][0], {dp[j + 1][1].f + extra, dp[j + 1][1].s});
            extra += p[j];
        }
        // Iterate over last location covered by the previous station
        extra = p[i];
        for(int j = i; j >= 0; j--) {
            dp[i + 1][1] = max(dp[i + 1][1], {dp[j][0].f + extra, dp[j][0].s});
            if(j == 0 || d[i] - d[j - 1] > delta) {
                break;
            }
            extra += (ld) p[j - 1] / p2[d[i] - d[j - 1]]; 
        }
        dp[i + 1][1].f -= penalty, ++dp[i + 1][1].s;
        dp[i + 1][0] = max(dp[i + 1][0], dp[i + 1][1]);
    }
    return dp[n][0];
}

int main() {
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> p[i] >> d[i];
    }
    p2[0] = 1;
    for(int i = 1; i <= delta; i++) {
        p2[i] = 2 * p2[i - 1];
    }
    ld lb = 0.0, ub = 1e7;
    pair<ld, int> res;
    for(int it = 0; it < 100; it++) {
        ld mid = (lb + ub) / 2;
        res = try_penalty(mid);
        if(res.s > k) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    ld penalty = (lb + ub) / 2;
    cout << fixed << setprecision(7) << res.f + penalty * k << endl;
}
/*
Observations:

1) We only need to be precise to the nearest 1e-6, so we just care about coordinates within ~27 units of a station
2) We only consider placing stations at population centers.
3) The above reduces this to an O(27nk) DP
4) You can remove a dimension for the above DP via Aliens Trick
*/