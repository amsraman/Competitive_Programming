#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int k, n, m; cin >> k >> n >> m;
    string necklace; cin >> necklace; int len = (int) necklace.length();
    pair<int, int> st; cin >> st.first >> st.second; --st.first, --st.second;
    string res = "impossible", lets = "ENWS"; vector<int> cur(len);
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<pair<int, int>> dirs = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
    auto ok = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m && !vis[x][y];
    };
    auto gen = [&](auto rec, int r, int c, int pos, int dir) -> bool {
        // pruning steps
        if(abs(r - st.first) + abs(c - st.second) > len - pos) {
            return false;
        }
        vis[r][c] = true;
        if(dir == -1) { // we're free to do whatever
            for(int i: {0, 1, 3, 2}) {
                auto [dx, dy] = dirs[i];
                if(!ok(r + dx, c + dy)) continue;
                cur[pos] = i;
                if(rec(rec, r + dx, c + dy, pos + 1, i)) {
                    return true;
                }
            }
            return false;
        }
        if(pos == (int) necklace.size() - 1) { // we're at the end
            int fin_dir = -1; bool works = true;
            for(int i = 0; i < 4; i++) {
                if(r + dirs[i].first == st.first && c + dirs[i].second == st.second) {
                    fin_dir = i;
                }
            }
            if(fin_dir == -1) works = false; // doesn't form a closed loop
            cur[pos] = fin_dir;
            if(fin_dir == dir) { // the last thing went straight
                if(necklace[pos] == 'B') works = false;
                if(necklace[0] == 'W' && cur[0] == cur[1]) works = false;
                if(necklace[pos - 1] == 'W' && cur[pos - 1] == cur[pos - 2]) works = false;
            } else {
                if(necklace[pos] == 'W') works = false;
                if(necklace[pos - 1] == 'B' || necklace[0] == 'B') works = false;
            }
            if(fin_dir == cur[0]) { // the first thing goes straight
                if(necklace[0] == 'B') works = false;
                if(necklace[1] == 'W' && cur[1] == cur[2]) works = false;
            } else {
                if(necklace[0] == 'W') works = false;
                if(necklace[pos] == 'B' || necklace[1] == 'B') works = false;
            }
            if(works) {
                return true;
            }
            vis[r][c] = false;
            return false;
        }
        bool can_turn = true, can_straight = true;
        if(necklace[pos] == 'B') can_straight = false;
        if(necklace[pos - 1] == 'B' || necklace[pos + 1] == 'B') can_turn = false;
        if(necklace[pos] == 'W') can_turn = false;
        if(pos > 2 && necklace[pos - 1] == 'W' && cur[pos - 2] == cur[pos - 3]) can_straight = false;
        bitset<4> can;
        auto [fx, fy] = dirs[dir];
        if(can_straight && ok(r + fx, c + fy)) {
            can[dir] = true;
        }
        if(can_turn) {
            for(int i = 1; i <= 3; i += 2) {
                auto [tx, ty] = dirs[(dir + i) % 4];
                if(!ok(r + tx, c + ty)) continue;
                can[(dir + i) % 4] = true;
            }
        }
        for(auto nxt_dir: {0, 1, 3, 2}) {
            if(!can[nxt_dir]) continue;
            cur[pos] = nxt_dir;
            if(rec(rec, r + dirs[nxt_dir].first, c + dirs[nxt_dir].second, pos + 1, nxt_dir)) {
                return true;
            }
        }
        vis[r][c] = false;
        return false;
    };
    if(gen(gen, st.first, st.second, 0, -1)) {
        res = "";
        for(int dir: cur) res += lets[dir];
    }
    cout << res << '\n';
}