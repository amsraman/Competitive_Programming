#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, h[200000];
ll ans;
vector<int> g[200000];

int dfs(int x, int p) {
    int mx, mx1 = 0, mx2 = 0;
    for(int u: g[x]) {
        if(u != p) {
            mx = dfs(u, x);
            if(mx > mx1) {
                mx2 = mx1, mx1 = mx;
            } else if(mx > mx2) {
                mx2 = mx;
            }
        }
    }
    int e1 = max(0, h[x] - mx1), e2 = max(0, h[x] - mx2);
    if(x == p) {
        ans += (e1 + e2);
    } else {
        ans += e1, mx1 += e1;
    }
    return mx1;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    int mx = 0;
    for(int i = 0; i < n; i++) {
        if(h[i] > h[mx]) {
            mx = i;
        }
    }
    dfs(mx, mx);
    cout << ans << endl;
}