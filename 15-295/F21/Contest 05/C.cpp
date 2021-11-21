#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, m;
ll p[100000], h[100000], sz[100000], good[100000], bad[100000];
vector<int> g[100000];
bool imp;

void dfs1(int x, int pr) {
    sz[x] = p[x];
    for(int i: g[x]) {
        if(i != pr) {
            dfs1(i, x);
            sz[x] += sz[i];
        }
    }
}

void dfs2(int x, int pr) {
    int tot_bad = p[x];
    for(int i: g[x]) {
        if(i != pr) {
            dfs2(i, x);
            tot_bad += bad[i];
        }
    }
    if(tot_bad < bad[x]) {
        imp = true;
    }
}

int main() {
    cin >> t;
    while(t--) {
        cin >> n >> m;
        for(int i = 0; i < n; i++) {
            cin >> p[i];
        }
        for(int i = 0; i < n; i++) {
            cin >> h[i];
        }
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        dfs1(0, 0);
        imp = false;
        for(int i = 0; i < n; i++) {
            if(abs(h[i]) % 2 != sz[i] % 2) {
                imp = true;
            }
            if(h[i] < - sz[i] || h[i] > sz[i]) {
                imp = true;
            }
            good[i] = (sz[i] + h[i]) / 2;
            bad[i] = sz[i] - good[i];
        }
        dfs2(0, 0);
        cout << (imp ? "NO" : "YES") << endl;
        for(int i = 0; i < n; i++) {
            g[i].clear();
        }
    }
}