#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 0xfffffffffffffff;

int n, l, reg[(1 << 18)], ans[(1 << 18)];
ll s, dist[(1 << 18)][8];
vector<pair<int, int>> g[(1 << 18)];
bool vis[(1 << 18)][18];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> l >> s;
    for(int i = 0, a, b; i < l; i++) {
        cin >> a >> b;
        g[b - 1].push_back({a - 1, i + 1});
    }
    for(int i = 0; i < n; i++) {
        cin >> reg[i];
    }
    for(int b = 0; b < 8; b++) {
        priority_queue<pair<ll, int>> q;
        for(int i = 0; i < n; i++) {
            if((reg[i] >> b) & 1) {
                q.push({0, i});
                dist[i][b] = 0;
            } else {
                dist[i][b] = INF;
            }
        }
        while(!q.empty()) {
            pair<ll, int> cur_el = q.top();
            int v = cur_el.s;
            q.pop();
            if(-cur_el.f > dist[v][b]) {
                continue;
            }
            for(pair<int, int> e: g[v]) {
                ll nxt_dis;
                if(e.s > dist[v][b] % l) {
                    nxt_dis = dist[v][b] + e.s - dist[v][b] % l;
                } else {
                    nxt_dis = dist[v][b] + l - (dist[v][b] % l) + e.s;
                }
                if(nxt_dis < dist[e.f][b]) {
                    dist[e.f][b] = nxt_dis;
                    q.push({-nxt_dis, e.f});
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 8; j++) {
            if(dist[i][j] <= s) {
                ans[i] |= (1 << j);
            }
        }
        cout << ans[i] << " ";
    }
    cout << '\n';
}