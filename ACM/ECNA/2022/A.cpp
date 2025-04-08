#include <bits/stdc++.h>

using namespace std;

template <typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
using state = pair<int, int>;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int c, r, e; cin >> c >> r >> e; --e;
    int c1, r1; char d1; cin >> c1 >> r1 >> d1; --c1, --r1;
    int c2, r2; char d2; cin >> c2 >> r2 >> d2; --c2, --r2;
    vector<vector<bool>> hw(r - 1, vector<bool>(c, false)), vw(r, vector<bool>(c - 1, false));
    int n; cin >> n;
    for(int i = 0, ci, ri; i < n; i++) {
        cin >> ci >> ri; --ci, --ri; hw[ri][ci] = true;
    }
    cin >> n;
    for(int i = 0, ci, ri; i < n; i++) {
        cin >> ci >> ri; --ci, --ri; vw[ri][ci] = true;
    }
    vector<vector<vector<vector<pair<int, int>>>>> dist(r + 1, vector<vector<vector<pair<int, int>>>>(c, vector<vector<pair<int, int>>>(r + 1, vector<pair<int, int>>(c, make_pair(1e9, 1e9)))));
    min_heap<pair<pair<int, int>, pair<state, state>>> q;
    vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; string rd = "ESWN";
    int df = (rd.find(d2) - rd.find(d1) + 4) % 4;
    state s1 = make_pair(r1, c1), s2 = make_pair(r2, c2);
    q.push({dist[r1 + 1][c1][r2 + 1][c2] = make_pair(0, 0), make_pair(s1, s2)});
    auto ok = [&](int x, int y) {
        return x >= 0 && x < r && y >= 0 && y < c;
    };
    auto wall = [&](int x, int y, int d) {
        if(x == -1 || (x == 0 && y == e && d == 2)) return false;
        if(d == 0) {
            return x == r - 1 || hw[x][y];
        } else if(d == 1) {
            return y == c - 1 || vw[x][y];
        } else if(d == 2) {
            return x == 0 || hw[x - 1][y];
        }
        return y == 0 || vw[x][y - 1];
    };
    auto move_forward = [&](int x, int y, int d) {
        if(x == -1) return make_pair(x, y); // once you're out you're out
        if(x == 0 && y == e && d == 2) return make_pair(-1, e); // escaping
        auto [dx, dy] = dirs[d];
        if(!ok(x + dx, y + dy) || wall(x, y, d)) return make_pair(x, y); // wall or oob?
        return make_pair(x + dx, y + dy);
    };
    pair<int, int> res;
    while(!q.empty()) {
        auto [d, cur_state] = q.top(); q.pop();
        auto [s1, s2] = cur_state;
        auto [steps, bumps] = d;
        auto [x1, y1] = s1;
        auto [x2, y2] = s2;
        if(d > dist[x1 + 1][y1][x2 + 1][y2]) continue;
        if(max(x1, x2) == -1) {
            res = d;
            break;
        }
        if(x1 == x2 && y1 == y2) continue;
        for(int d1 = 0; d1 < 4; d1++) {
            int d2 = (d1 + df) % 4;
            auto [nx1, ny1] = move_forward(x1, y1, d1);
            auto [nx2, ny2] = move_forward(x2, y2, d2);
            auto new_state = make_pair(make_pair(nx1, ny1), make_pair(nx2, ny2));
            auto new_dist = make_pair(steps + 1, bumps + wall(x1, y1, d1) + wall(x2, y2, d2));
            if(new_dist < dist[nx1 + 1][ny1][nx2 + 1][ny2]) {
                dist[nx1 + 1][ny1][nx2 + 1][ny2] = new_dist;
                q.push({new_dist, new_state});
            }
        }
    }
    cout << res.first << " " << res.second << '\n';
}