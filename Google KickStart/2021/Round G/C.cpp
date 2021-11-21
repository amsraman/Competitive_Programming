#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int t, n, k, b[5000], best[1000001], ans;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> k;
        for(int i = 0; i < n; i++) {
            cin >> b[i];
        }
        for(int i = 1; i <= 1e6; i++) {
            best[i] = INF;
        }
        ans = INF;
        for(int i = n - 1; i >= 0; i--) {
            int sum = 0;
            for(int j = i; j >= 0; j--) {
                sum += b[j];
                if(sum > k) {
                    break;
                }
                ans = min(ans, best[k - sum] + (i - j + 1));
            }
            sum = 0;
            for(int j = i; j < n; j++) {
                sum += b[j];
                if(sum > k) {
                    break;
                }
                best[sum] = min(best[sum], j - i + 1);
            }
        }
        cout << "Case #" << _ << ": " << (ans == INF ? -1 : ans) << endl;
    }
}