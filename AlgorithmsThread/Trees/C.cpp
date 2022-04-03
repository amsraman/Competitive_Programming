#include <bits/stdc++.h>

using namespace std;

int n, q, t, in[300000], out[300000], par[300000][19];
vector<int> g[300000];

void dfs(int x, int p) {
    in[x] = t++;
    for(int u: g[x]) {
        if(u != p) {
            par[u][0] = x;
            dfs(u, x);
        }
    }
    out[x] = t++;
}

bool isAnc(int x, int y) {
    return (in[x] <= in[y] && out[x] >= out[y]);
}

int go_up(int x, int d) {
    for(int i = 0; i < 19; i++) {
        if((d >> i) & 1) {
            x = par[x][i];
        }
    }
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    dfs(0, 0);
    for(int i = 1; i < 19; i++) {
        for(int j = 0; j < n; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
    cin >> q;
    for(int i = 0, a, b, c; i < q; i++) {
        cin >> a >> b >> c;
        --a, --b;
        int d1 = 0, d2 = 0, ta = a, tb = b;
        for(int i = 18; i >= 0; i--) {
            if(!isAnc(par[ta][i], b)) {
                ta = par[ta][i];
                d1 += (1 << i);
            }
            if(!isAnc(par[tb][i], a)) {
                tb = par[tb][i];
                d2 += (1 << i);
            }
        }
        d1 += (int) (!isAnc(a, b));
        d2 += (int) (!isAnc(b, a));
        if(c <= d1) {
            cout << go_up(a, c) + 1 << '\n';
        } else {
            c = min(c, d1 + d2), c -= d1;
            cout << go_up(b, d2 - c) + 1 << '\n';
        }
    }
}