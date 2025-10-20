#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("two_apples_a_day_input.txt");
    ofstream cout("output.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<int> a(2 * n - 1);
        for(int i = 0; i < 2 * n - 1; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        long long ans = 2e9;
        auto try_sum = [&](int x) {
            vector<int> cur = a;
            long long tot = 1LL * x * n;
            for(int val: a) {
                tot -= val;
            }
            cur.push_back(tot);
            sort(cur.begin(), cur.end());
            for(int i = 0, j = 2 * n - 1; i < j; i++, j--) {
                if(cur[i] + cur[j] != x) return;
            }
            if(tot > 0) ans = min(ans, tot);
        };
        if(n > 1) {
            try_sum(a[0] + a[2 * n - 2]);
            try_sum(a[0] + a[2 * n - 3]);
            try_sum(a[1] + a[2 * n - 2]);
        } else {
            ans = 1;
        }
        cout << "Case #" << _ << ": " << (ans == 2e9 ? -1 : ans) << '\n';
    }
}