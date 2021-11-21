#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, k, v, a[5000], cur[5000], prv[5001][5001];
bool dp[5001][5001], ans;

signed main() {
    cin >> n >> k >> v;
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    dp[0][0] = true;
    for(int i = 0; i < n; i++) {
        int loc = a[i] % k;
        for(int j = 0; j < k; j++) {
            dp[i + 1][j] = dp[i][j];
        }
        vector<int> to_update;
        for(int j = 0; j < k; j++) {
            if(dp[i][(j - loc + k) % k]) {
                dp[i + 1][j] = true;
                prv[i + 1][j] = cur[(j - loc + k) % k];
                to_update.push_back(j);
            }
        }
        for(int j: to_update) {
            cur[j] = i + 1;
        }
    }
    ans = (sum >= v && cur[(v % k)] > 0);
    if(v % k == 0 && sum >= v) {
        cout << "YES" << endl;
        for(int i = 1; i < n; i++) {
            if(a[i] > 0) {
                cout << (a[i] + k - 1) / k << " " << i + 1 << " " << 1 << endl;
            }
        }
        if(v > 0) {
            cout << v / k << " " << 1 << " " << 2 << endl;
        }
    } else if(ans) {
        cout << "YES" << endl;
        vector<int> buckets;
        int cur_bucket = cur[(v % k)], cur_value = (v % k);
        while(cur_bucket > 0) {
            buckets.push_back(cur_bucket - 1);
            int val = a[cur_bucket - 1] % k;
            cur_bucket = prv[cur_bucket][cur_value];
            cur_value = (cur_value - val + k) % k;
        }
        sum = a[buckets[0]];
        for(int i = 1; i < buckets.size(); i++) {
            if(a[buckets[i]] > 0) {
                cout << (a[buckets[i]] + k - 1) / k << " " << buckets[i] + 1 << " " << buckets[0] + 1 << endl;
            }
            sum += a[buckets[i]], a[buckets[i]] = 0;
        }
        if(sum > v) {
            cout << (sum - v) / k << " " << buckets[0] + 1 << " " << (buckets[0] + 1) % n + 1 << endl;
        } else if(sum < v) {
            for(int i = 0; i < n; i++) {
                if(i != buckets[0] && i != (buckets[0] + 1) % n) {
                    if(a[i] > 0) {
                        cout << (a[i] + k - 1) / k << " " << i + 1 << " " << (buckets[0] + 1) % n + 1 << endl;
                    }
                }
            }
            cout << (v - sum) / k << " " << (buckets[0] + 1) % n + 1 << " " << buckets[0] + 1 << endl;
        }
    } else {
        cout << "NO" << endl;
    }
}