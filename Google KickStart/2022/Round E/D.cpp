#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 0xfffffffffffffff;

int n, p, m, k[4], c[10];
pair<int, int> st, pos[10];
ll dp[(1 << 10)][10][10][22], ans;
char op[4];
pair<int, int> dir[4] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};

ll trav(ll x, int d) {
    if(x == -INF) {
        return x;
    }
    if(op[d] == '+') {
        return x + k[d];
    } else if(op[d] == '-') {
        return x - k[d];
    } else if(op[d] == '*') {
        return x * k[d];
    } else if(x >= 0) {
        return x / k[d];
    }
    return (x - k[d] + 1) / k[d];
}

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> p >> m >> st.f >> st.s;
        --st.f, --st.s;
        for(int i = 0; i < 4; i++) {
            cin >> op[i] >> k[i];
        }
        for(int i = 0; i < p; i++) {
            cin >> pos[i].f >> pos[i].s >> c[i];
            --pos[i].f, --pos[i].s;
        }
        for(int i = 0; i < (1 << p); i++) {
            for(int x = 0; x < n; x++) {
                for(int y = 0; y < n; y++) {
                    for(int tm = 0; tm <= m; tm++) {
                        dp[i][x][y][tm] = -INF;
                    }
                }
            }
        }
        dp[0][st.f][st.s][0] = 0;
        ans = -INF;
        for(int ct = 0; ct <= m; ct++) {
            for(int i = 0; i < (1 << p); i++) {
                for(int x = 0; x < n; x++) {
                    for(int y = 0; y < n; y++) {
                        for(int cust = 0; cust < p; cust++) {
                            if(((i >> cust) & 1) || pos[cust].f != x || pos[cust].s != y) {
                                continue;
                            }
                            ll nxt = (dp[i][x][y][ct] == -INF ? -INF : dp[i][x][y][ct] + c[cust]);
                            dp[i ^ (1 << cust)][x][y][ct] = max(dp[i ^ (1 << cust)][x][y][ct], nxt);
                        }
                        dp[i][x][y][ct + 1] = max(dp[i][x][y][ct + 1], dp[i][x][y][ct]);
                        for(int d = 0; d < 4; d++) {
                            int nx = x + dir[d].f, ny = y + dir[d].s;
                            if(nx < 0 || nx >= n || ny < 0 || ny >= n) {
                                continue;
                            }
                            dp[i][nx][ny][ct + 1] = max(dp[i][nx][ny][ct + 1], trav(dp[i][x][y][ct], d));
                        }
                    }
                }
            }
        }
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < n; y++) {
                for(int tm = 0; tm <= m; tm++) {
                    ans = max(ans, dp[(1 << p) - 1][x][y][tm]);
                }
            }
        }
        cout << "Case #" << _ << ": ";
        if(ans == -INF) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << ans << endl;
        }
    }
}