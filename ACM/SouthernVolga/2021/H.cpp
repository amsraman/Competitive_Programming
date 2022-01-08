#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, num_m, m[200000], k[200000];
pair<int, int> cur_best = {0, 1};

bool cmp(pair<int, int> f1, pair<int, int> f2) {
    // Return true if f1 is better than f2
    return (ll) f2.s * f1.f >= (ll) f1.s * f2.f;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> m[i] >> k[i];
        num_m = max(num_m, m[i]);
    }
    for(int i = 1; i <= min(num_m, 20); i++) {
        vector<ll> sum(num_m, 0);
        for(int j = 0; j < n; j++) {
            sum[m[j] - 1] += min(i, k[j]);
        }
        sort(sum.begin(), sum.end());
        reverse(sum.begin(), sum.end());
        ll tot = 0;
        for(int j = 0; j < i; j++) {
            tot += sum[j];
        }
        if(cmp({tot, i}, cur_best)) {
            cur_best = {tot, i};
        }
    }
    cout << cur_best.s << endl;
    vector<ll> sum(num_m, 0LL);
    vector<pair<int, int>> msg;
    for(int i = 0; i < n; i++) {
        sum[m[i] - 1] += min(cur_best.s, k[i]);
    }
    for(int i = 0; i < num_m; i++) {
        msg.push_back({sum[i], i});
    }
    sort(msg.begin(), msg.end());
    reverse(msg.begin(), msg.end());
    for(int i = 0; i < cur_best.s; i++) {
        cout << msg[i].s + 1 << " ";
    }
    cout << endl;
}
