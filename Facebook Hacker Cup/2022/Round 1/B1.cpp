#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int main() {
    ifstream cin("watering_well_chapter_1_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, q, ans = 0;
        cin >> n;
        vector<int> x_ct(3001, 0), y_ct(3001, 0), x_sum(3001, 0), y_sum(3001, 0);
        for(int i = 0, a, b; i < n; i++) {
            cin >> a >> b;
            ++x_ct[a], ++y_ct[b];
        }
        for(int i = 0, x_num = 0, x_diff = 0, x_tot = 0, y_num = 0, y_diff = 0, y_tot = 0; i <= 3000; i++) {
            x_diff = (1LL * x_diff + 2 * x_num) % mod, y_diff = (1LL * y_diff + 2 * y_num) % mod;
            x_tot = (x_tot + x_diff) % mod, y_tot = (y_tot + y_diff) % mod;
            x_sum[i] = (x_sum[i] + x_tot) % mod, y_sum[i] = (y_sum[i] + y_tot) % mod;
            x_diff = (x_diff - x_ct[i] + mod) % mod, y_diff = (y_diff - y_ct[i] + mod) % mod;
            x_num += x_ct[i], y_num += y_ct[i];
        }
        for(int i = 3000, x_num = 0, x_diff = 0, x_tot = 0, y_num = 0, y_diff = 0, y_tot = 0; i >= 0; i--) {
            x_diff = (1LL * x_diff + 2 * x_num) % mod, y_diff = (1LL * y_diff + 2 * y_num) % mod;
            x_tot = (x_tot + x_diff) % mod, y_tot = (y_tot + y_diff) % mod;
            x_sum[i] = (x_sum[i] + x_tot) % mod, y_sum[i] = (y_sum[i] + y_tot) % mod;
            x_diff = (x_diff - x_ct[i] + mod) % mod, y_diff = (y_diff - y_ct[i] + mod) % mod;
            x_num += x_ct[i], y_num += y_ct[i];
        }
        cin >> q;
        for(int i = 0, x, y; i < q; i++) {
            cin >> x >> y;
            ans = (1LL * ans + x_sum[x] + y_sum[y]) % mod;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}