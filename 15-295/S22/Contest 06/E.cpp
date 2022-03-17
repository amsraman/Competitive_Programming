#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 1e15;

int n, m, q, ans;
ll dist[600][600];
vector<array<int, 3>> g[600];
vector<pair<int, int>> grp[600];
bool useful[360000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dist[i][j] = (i == j ? 0 : INF);
        }
    }
    for(int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        g[u - 1].push_back({v - 1, w, i});
        g[v - 1].push_back({u - 1, w, i});
        dist[u - 1][v - 1] = dist[v - 1][u - 1] = w;
    }
    cin >> q;
    for(int i = 0, u, v, l; i < q; i++) {
        cin >> u >> v >> l;
        grp[u - 1].push_back({v - 1, l});
        grp[v - 1].push_back({u - 1, l});
    }
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        vector<ll> mn(n, INF);
        vector<bool> done(n, false);
        for(pair<int, int> e: grp[i]) {
            mn[e.f] = -e.s;
        }
        for(int i = 0; i < n; i++) {
            int argmin = -1;
            for(int j = 0; j < n; j++) {
                if(!done[j] && (argmin == -1 || mn[j] < mn[argmin])) {
                    argmin = j;
                }
            }
            done[argmin] = true;
            for(array<int, 3> e: g[argmin]) {
                mn[e[0]] = min(mn[e[0]], mn[argmin] + e[1]);
            }
        }
        for(int u = 0; u < n; u++) {
            for(array<int, 3> e: g[u]) {
                if(-dist[i][u] - mn[e[0]] >= e[1]) {
                    useful[e[2]] = true;
                }
            }
        }
    }
    for(int i = 0; i < m; i++) {
        if(useful[i]) {
            ++ans;
        }
    }
    cout << ans << '\n';
}