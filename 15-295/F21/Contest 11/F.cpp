#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, mx, r1, tot, c[200000], dep[200000], max_depth[200000], col[200000], ans[200000];
vector<int> g[200000];
stack<pair<int, int>> st;

void ins(int x) {
    tot += (col[x] == 0);
    ++col[x];
}

void rem(int x) {
    --col[x];
    tot -= (col[x] == 0);
}

void dfs1(int x, int p) {
    if(dep[x] > dep[mx]) {
        mx = x;
    }
    max_depth[x] = 0;
    for(int i: g[x]) {
        if(i != p) {
            dep[i] = dep[x] + 1;
            dfs1(i, x);
            max_depth[x] = max(max_depth[x], max_depth[i]);
        }
    }
    ++max_depth[x];
}

void dfs2(int x, int p) {
    vector<int> children;
    for(int i: g[x]) {
        if(i != p) {
            children.push_back(i);
        }
    }
    for(int i = 1; i < children.size(); i++) {
        if(max_depth[children[i]] > max_depth[children[0]]) {
            swap(children[0], children[i]);
        }
    }
    int mx_len = 0;
    for(int i = 1; i < children.size(); i++) {
        mx_len = max(mx_len, max_depth[children[i]]);
    }
    for(int i: children) {
        while(!st.empty() && st.top().f >= dep[x] - mx_len) {
            rem(c[st.top().s]);
            st.pop();
        }
        ins(c[x]);
        st.push({dep[x], x});
        dfs2(i, x);
        if(!st.empty() && st.top().s == x) {
            rem(c[st.top().s]);
            st.pop();
        }
        mx_len = max(mx_len, max_depth[i]);
    }
    if(!children.empty()) {
        while(!st.empty() && st.top().f >= dep[x] - mx_len) {
            rem(c[st.top().s]);
            st.pop();
        }
    }
    ans[x] = max(ans[x], tot);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    for(int i = 0; i < n; i++) {
        cin >> c[i];
    }
    dfs1(0, 0);
    r1 = mx, dep[r1] = 0;
    dfs1(r1, r1);
    dfs2(r1, r1);
    r1 = mx, dep[r1] = 0;
    dfs1(r1, r1);
    dfs2(r1, r1);
    for(int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }
}