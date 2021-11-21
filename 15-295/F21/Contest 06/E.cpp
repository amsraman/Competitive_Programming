#include <bits/stdc++.h>
typedef long double ld;
#define f first
#define s second

using namespace std;

int n;
ld cost[676][676];
string s[100000];
vector<int> g[676];

int conv(char x, char y) {
    return 26 * (x - 'a') + (y - 'a');
}

bool ok(ld offset) {
    vector<ld> dist(676, 0.0);
    int lst_move;
    for(int i = 0; i < 676; i++) {
        lst_move = -1;
        for(int j = 0; j < 676; j++) {
            for(int k: g[j]) {
                if(dist[j] + cost[j][k] + offset < dist[k]) {
                    dist[k] = dist[j] + cost[j][k] + offset;
                    lst_move = j;
                }
            }
        }
    }
    return lst_move == -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> s[i];
        int len = s[i].length(), v1 = conv(s[i][0], s[i][1]), v2 = conv(s[i][len - 2], s[i][len - 1]);
        if(cost[v1][v2] == 0) {
            g[v1].push_back(v2);
        }
        cost[v1][v2] = min(cost[v1][v2], (ld) -len);
    }
    ld lb = 0, ub = 200.0;
    while(lb + 1e-3 < ub) {
        ld mid = (lb + ub) / 2;
        if(ok(mid)) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    cout << fixed << setprecision(9) << ub << '\n';
}