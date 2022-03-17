#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, sz[10001];
ll mx1, mx2;
vector<int> g[10001];

void dfs(int x, int p) {
    sz[x] = 1;
    ll cur = 1LL * n * (n - 1) / 2;
    vector<int> st;
    for(int u: g[x]) {
        if(u != p) {
            dfs(u, x);
            sz[x] += sz[u];
            st.push_back(sz[u]);
        }
    }
    if(x != p) {
        st.push_back(n - sz[x]);
    }
    sort(st.begin(), st.end());
    for(int i: st) {
        cur -= (1LL * i * (i - 1)) / 2;
    }
    cur -= (n - 1);
    if(cur > mx1) {
        mx1 = cur;
        if(st.size() == 1) {
            mx2 = mx1;
        } else {
            mx2 = mx1 - (1LL * st[st.size() - 1] * st[st.size() - 2]);
        }
    }
}

int main() {
    cin >> n;
    for(int i = 0, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    n++;
    dfs(0, 0);
    cout << mx1 << " " << mx2 << endl;
}