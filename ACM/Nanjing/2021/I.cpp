#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int INF = 0x3f3f3f3f;

int t, h, n, m, ans;
pair<int, int> board[100000], coin[100000];
map<int, int> rec;

int up_setting(int x, int y) {
    return (x - y + 2 * h) % (2 * h);
}

int down_setting(int x, int y) {
    return (x + y) % (2 * h);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> h >> n;
        vector<pair<pair<int, int>, bool>> ord;
        for(int i = 0; i < n; i++) {
            cin >> board[i].f >> board[i].s;
            ord.push_back({board[i], true});
        }
        cin >> m;
        for(int i = 0; i < m; i++) {
            cin >> coin[i].f >> coin[i].s;
            ord.push_back({coin[i], false});
        }
        sort(ord.begin(), ord.end());
        rec[0] = 0;
        for(int i = 0; i < n + m; i++) {
            int ls = down_setting(ord[i].f.f, ord[i].f.s);
            int rs = up_setting(ord[i].f.f, ord[i].f.s);
            if(!rec.count(ls)) {
                rec[ls] = -INF;
            }
            if(!rec.count(rs)) {
                rec[rs] = -INF;
            }
            if(ord[i].s) {
                // Board
                if(rec[ls] < rec[rs]) {
                    rec[ls] = rec[rs];
                } else {
                    rec[rs] = rec[ls];
                }
            } else {
                // Coin
                ++rec[ls], ++rec[rs];
            }
            ans = max({ans, rec[ls], rec[rs]});
        }
        cout << ans << '\n';
        rec.clear(), ans = 0;
    }
}