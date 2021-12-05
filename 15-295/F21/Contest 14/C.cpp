#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int w, l, n;
long double dp[1001];
pair<int, int> p[1000];

int main() {
    cin >> w >> l >> n;
    for(int i = 0; i < n; i++) {
        cin >> p[i].f >> p[i].s;
    }
    long double dl = l * 60.0;
    dp[0] = 0;
    for(int i = 0; i < n; i++) {
        long long total_weight = p[i].f;
        int min_speed = p[i].s;
        dp[i + 1] = 1e17;
        for(int j = i; j >= 0; j--) {
            dp[i + 1] = min(dp[i + 1], dp[j] + dl / min_speed);
            if(j == 0) {
                break;
            }
            total_weight += p[j - 1].f;
            min_speed = min(min_speed, p[j - 1].s);
            if(total_weight > w) {
                break;
            }
        }
    }
    cout << fixed << setprecision(9) << dp[n] << endl;
}