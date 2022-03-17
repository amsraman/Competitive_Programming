#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, m, adj[3000][3000], path[3000][3000];
ll ans;
pair<int, int> edges[30000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> edges[i].f >> edges[i].s;
        --edges[i].f, --edges[i].s;
        adj[edges[i].f][edges[i].s] = 1;
    }
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(adj[edges[i].s][j]) {
                ++path[edges[i].f][j];
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) {
                ans += 1LL * path[i][j] * (path[i][j] - 1) / 2;
            }
        }
    }
    cout << ans << '\n';
}