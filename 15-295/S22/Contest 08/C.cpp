#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, q, mx, x[1000], nxt[1000001];
ll a[100000], ans;
vector<int> g[100000];
bool pos[1000001], bad;

void dfs(int u, int p) {
    ll cm = a[u];
    for(int v: g[u]) {
        if(v != p) {
            dfs(v, u);
            cm = max(cm, a[v]);
        }
    }
    ll df = max(0LL, cm - a[u]);
    if(df > mx) {
        bad = true;
    } else {
        a[u] += nxt[df];
    }
    ans += a[u];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    for(int i = 0; i < q; i++) {
        cin >> x[i];
    }
    sort(x, x + q);
    pos[0] = true;
    for(int i = 0; i < q; i++) {
        for(int j = mx; j >= 0; j--) {
            pos[j + x[i]] |= pos[j];
        }
        mx += x[i];
    }
    for(int i = mx, j; i >= 0; i--) {
        if(pos[i]) {
            j = i;
        }
        nxt[i] = j;
    }
    dfs(0, 0);
    cout << (bad ? -1 : ans) << '\n';
}