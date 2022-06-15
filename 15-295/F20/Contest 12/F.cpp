#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int main() {
    vector<vector<int>> grid(4, vector<int>(4));
    vector<pair<int, int>> pos(16);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cin >> grid[i][j];
            pos[grid[i][j] - 1] = {i, j};
        }
    }
    auto cmp = [](pair<int, int> v1, pair<int, int> v2) {
        // returns if v1 < v2
        return (v1.f * v2.s - v2.f * v1.s) > 0;
    };
    vector<pair<int, int>> angs;
    map<pair<int, int>, int> ang_ind;
    for(int i = -4; i <= 4; i++) {
        for(int j = -4; j <= 4; j++) {
            int g = abs(__gcd(i, j));
            if(i != 0 || j != 0) {
                angs.push_back({i / g, j / g});
            }
        }
    }
    sort(angs.begin(), angs.end(), cmp);
    angs.erase(unique(angs.begin(), angs.end()), angs.end());
    int sz = 2 * angs.size(), ans = 100;
    for(int i = 0; i < sz; i += 2) {
        ang_ind[angs[i >> 1]] = i;
    }
    vector<vector<int>> dp(16, vector<int>(sz, 100));
    for(int i = 0; i < sz; i++) {
        dp[0][i] = 1;
    }
    for(int i = 0; i < 15; i++) {
        int g = abs(__gcd(pos[i + 1].f - pos[i].f, pos[i + 1].s - pos[i].s));
        pair<int, int> nxt_vec = {(pos[i + 1].f - pos[i].f) / g, (pos[i + 1].s - pos[i].s) / g};
        int ind = ang_ind[nxt_vec];
        for(int j = 0; j < sz; j++) {
            if(j == ind) {
                dp[i + 1][ind] = min(dp[i + 1][ind], dp[i][ind]);
                continue;
            } else if(abs(j - ind) == (sz >> 1)) {
                dp[i + 1][ind] = min(dp[i + 1][ind], dp[i][j] + 1);
                continue;
            }
            pair<int, int> interval = {ang_ind[nxt_vec], (j + (sz >> 1)) % sz};
            int dist = interval.f < interval.s ? interval.s - interval.f + (j & 1): sz - interval.f + interval.s + (j & 1);
            if(dist > sz - dist) {
                swap(interval.f, interval.s);
                if(interval.f & 1 ^ 1) {
                    ++interval.f;
                }
            } else if(interval.s & 1 ^ 1) {
                interval.s = (interval.s + sz - 1) % sz;
            }
            for(int k = 0; k < sz; k++) {
                if(interval.f < interval.s && k >= interval.f && k <= interval.s) {
                    dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + 1);
                } else if(interval.f > interval.s && (k >= interval.f || k <= interval.s)) {
                    dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + 1);
                }
            }
        }
    }
    for(int i = 0; i < sz; i++) {
        ans = min(ans, dp[15][i]);
    }
    cout << ans << endl;
}