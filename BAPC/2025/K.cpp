#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    vector<bool> bad(1 << n, false); int all = (1 << n) - 1;
    for(int i = 0; i < m; i++) {
        string st; cin >> st;
        int msk = 0;
        for(char c: st) {
            msk = 2 * msk + c - '0';
        }
        bad[msk] = true;
    }
    for(int bt = 0; bt < n; bt++) {
        for(int msk = 0; msk < 1 << n; msk++) {
            if((msk >> bt) & 1) {
                bad[msk] = bad[msk] | bad[msk ^ (1 << bt)];
            }
        }
    }
    vector<vector<vector<int>>> dist(1 << n, vector<vector<int>>(k + 1, vector<int>(2, 1e9))); int res = 1e9;
    deque<tuple<int, int, int>> q; q.emplace_back(1, 0, k); dist[0][k][0] = 1;
    while(!q.empty()) {
        auto [d, msk, rem] = q.front(); q.pop_front();
        if(msk == ((1 << n) - 1)) res = min(res, d);
        if(d > dist[msk][rem][d & 1 ^ 1]) continue;
        bool is_bad = (d % 2 == 1 && bad[all ^ msk]) || (d % 2 == 0 && bad[msk]);
        if(!is_bad && d + 1 < dist[msk][k][d & 1]) {
            q.emplace_back(d + 1, msk, k);
            dist[msk][k][d & 1] = d + 1;
        }
        if(rem == 0) continue;
        for(int bt = 0; bt < n; bt++) {
            int new_msk = msk ^ (1 << bt);
            bool can_move = (d & 1) ^ ((msk >> bt) & 1);
            if(can_move && d < dist[new_msk][rem - 1][d & 1 ^ 1]) {
                q.emplace_front(d, new_msk, rem - 1);
                dist[new_msk][rem - 1][d & 1 ^ 1] = d;
            }
        }
    }
    if(res == 1e9) res = -1;
    cout << res << '\n';
}
/*
dp[msk] = minimum number of moves for msk to be on the other side of the bridge

note that the bad set condition is STRICTLY a feature of msk itself, not the path taken to get there
meaning some states are just bad. they can't ever be intermediate stages in the process

the other limitation is that the boat is of size k
*/