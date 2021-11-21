#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int k;
pair<int, int> dir[8] = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}}, pv[8][8];
bool full[8][8], vis[8][8];
vector<string> ans;

string conv(int x, int y) {
    string ret = "";
    ret += char('a' + y);
    ret += char('0' + x + 1);
    return ret;
}

bool ok(int x, int y) {
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

int main() {
    cin >> k;
    for(int i = 0; i < k; i++) {
        string move;
        cin >> move;
        full[move[1] - '0' - 1][move[0] - 'a'] = true;
    }
    for(int i = 0; i < k; i++) {
        queue<pair<int, int>> q;
        int cur_x = i / 8, cur_y = i % 8;
        if(full[cur_x][cur_y]) {
            continue;
        }
        q.push({cur_x, cur_y});
        memset(vis, false, sizeof(vis));
        vis[i / 8][i % 8] = true;
        while(!q.empty()) {
            cur_x = q.front().f, cur_y = q.front().s;
            q.pop();
            if(8 * cur_x + cur_y >= i && full[cur_x][cur_y]) {
                break;
            }
            for(pair<int, int> d: dir) {
                if(ok(cur_x + d.f, cur_y + d.s) && !vis[cur_x + d.f][cur_y + d.s]) {
                    q.push({cur_x + d.f, cur_y + d.s});
                    pv[cur_x + d.f][cur_y + d.s] = {cur_x, cur_y};
                    vis[cur_x + d.f][cur_y + d.s] = true;
                }
            }
        }
        vector<pair<int, int>> path;
        while(8 * cur_x + cur_y != i) {
            path.push_back({cur_x, cur_y});
            int pv_x = pv[cur_x][cur_y].f, pv_y = pv[cur_x][cur_y].s;
            cur_x = pv_x, cur_y = pv_y;
        }
        path.push_back({cur_x, cur_y});
        reverse(path.begin(), path.end());
        full[cur_x][cur_y] = true;
        for(int i = 1; i < path.size(); i++) {
            if(full[path[i].f][path[i].s]) {
                for(int j = i; (path[j].f != cur_x || path[j].s != cur_y); j--) {
                    ans.push_back(conv(path[j].f, path[j].s) + "-" + conv(path[j - 1].f, path[j - 1].s));
                }
                cur_x = path[i].f, cur_y = path[i].s;
            }
        }
        full[cur_x][cur_y] = false;
    }
    cout << ans.size() << endl;
    for(string mv: ans) {
        cout << mv << endl;
    }
}