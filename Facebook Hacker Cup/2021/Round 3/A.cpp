#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

int t, n, m;

int choose2(int x) {
    return (1LL * x * (x - 1) / 2) % mod;
}

int main() {
    freopen("reporeting_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> m;
        int cur = choose2(n), ans = 1;
        set<pair<int, int>> intervals;
        for(int i = 0; i < n; i++) {
            intervals.insert({i, i});
        }
        for(int i = 0, a, b; i < m; i++) {
            cin >> a >> b;
            --a, --b;
            if(a > b) {
                swap(a, b);
            }
            auto it = intervals.lower_bound({a, -1});
            if(it == intervals.end() || it->f > a) {
                --it;
            }
            vector<pair<int, int>> to_remove;
            while(it != intervals.end() && it->f <= b) {
                to_remove.push_back(*it);
                ++it;
            }
            if(to_remove.empty()) {
                ans = (1LL * ans * cur) % mod;
                continue;
            }
            for(pair<int, int> p: to_remove) {
                cur = (cur - choose2(p.s - p.f + 1) + mod) % mod;
                intervals.erase(p);
            }
            cur = (cur + choose2(to_remove.back().s - to_remove[0].f + 1))% mod;
            intervals.insert({to_remove[0].f, to_remove.back().s});
            ans = (1LL * ans * cur) % mod;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}
