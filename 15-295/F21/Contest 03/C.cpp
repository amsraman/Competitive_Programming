#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, dp[100000];
pair<int, int> pos[100000];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> pos[i].f >> pos[i].s;
    }
    sort(pos, pos + n);
    for(int i = 1; i < n; i++) {
        if(pos[0].f >= pos[i].f - pos[i].s) {
            dp[i] = i;
            continue;
        }
        int lb = 0, ub = n - 1;
        while(lb < ub) {
            int mid = (lb + ub + 1) / 2;
            if(pos[mid].f < pos[i].f - pos[i].s) {
                lb = mid;
            } else {
                ub = mid - 1;
            }
            dp[i] = (i - ub - 1) + dp[ub];
        }
    }
    int ans = 0x3f3f3f3f;
    for(int i = 0; i < n; i++) {
        ans = min(ans, (n - i - 1) + dp[i]);
    }
    cout << ans << endl;
}