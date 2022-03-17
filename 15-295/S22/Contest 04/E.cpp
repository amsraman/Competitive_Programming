#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, c[100000], ans;
vector<int> g[100000];
map<int, int> cols[100000];

void dfs(int x, int p) {
    if(g[x].size() == 1 && x != p) {
        cols[x][c[x]] = 1;
        return;
    }
    map<int, int> sm;
    int lg = -1, mx = 1;
    for(int u: g[x]) {
        if(u != p) {
            dfs(u, x);
            if(lg == -1 || cols[u].size() > cols[lg].size()) {
                lg = u;
            }
        }
    }
    for(int u: g[x]) {
        if(u != p && u != lg) {
            for(auto it: cols[u]) {
                ++sm[it.f];
            }
        }
    }
    for(auto it: sm) {
        mx = max(mx, it.s + cols[lg][it.f]);
    }
    ans -= mx;
    if(mx == 1) {
        swap(cols[x], cols[lg]);
        for(auto it: sm) {
            cols[x][it.f] = 1;
        }
    } else {
        for(auto it: sm) {
            if(it.s + cols[lg][it.f] == mx) {
                cols[x][it.f] = 1;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0, p; i < n - 1; i++) {
        cin >> p;
        g[p - 1].push_back(i + 1);
        g[i + 1].push_back(p - 1);
    }
    for(int i = 0; i < n; i++) {
        cin >> c[i];
    }
    ans = n;
    dfs(0, 0);
    cout << ans << '\n';
}