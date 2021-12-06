#include <bits/stdc++.h>

using namespace std;

int t, n, a, b, l, piv, cur, longest_branch[100000], par[100000], depth[100000], lowest_depth[100000], in[100000], out[100000];
vector<int> g[100000];
bool ans;

void dfs(int x, int p, int d = 1) {
    if(x == b) {
        l = d;
    }
    longest_branch[x] = 0;
    for(int i: g[x]) {
        if(i != p) {
            dfs(i, x, d + 1);
            longest_branch[x] = max(longest_branch[x], longest_branch[i]);
        }
    }
    ++longest_branch[x];
}

void dfs2(int x, int p, int up = 0) {
    int sz = g[x].size() - (x != p), good_branches = (up >= (l - 1));
    vector<int> down, pf, sf;
    pf.push_back(0), sf.push_back(0);
    for(int i: g[x]) {
        if(i != p) {
            down.push_back(i);
            if(longest_branch[i] >= (l - 1)) {
                ++good_branches;
            }
        }
    }
    if(good_branches >= 3) {
        piv = x, depth[x] = 0;
    }
    for(int i = 0; i < sz; i++) {
        pf.push_back(max(pf.back(), longest_branch[down[i]]));
        sf.push_back(max(sf.back(), longest_branch[down[sz - i - 1]]));
    }
    reverse(sf.begin(), sf.end());
    for(int i = 0; i < sz; i++) {
        dfs2(down[i], x, 1 + max(up, max(pf[i], sf[i + 1])));
    }
}

void dfs3(int x, int p) {
    in[x] = cur++;
    for(int i: g[x]) {
        if(i != p) {
            lowest_depth[i] = depth[i] = depth[x] + 1;
            dfs3(i, x);
            par[i] = x;
            lowest_depth[x] = max(lowest_depth[x], lowest_depth[i]);
        }
    }
    out[x] = cur++;
}

bool isAnc(int x, int y) {
    return (in[x] <= in[y] && out[x] >= out[y]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> a >> b;
        --a, --b;
        for(int i = 0, u, v; i < n - 1; i++) {
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        piv = -1, dfs(a, a), dfs2(a, a);
        ans = false, cur = 0;
        if(piv != -1) {
            par[piv] = piv, depth[piv] = 0;
            dfs3(piv, piv);
            int d1 = depth[a], d2 = depth[b];
            bool go = true;
            while(go) {
                go = false;
                for(; d1 < lowest_depth[a]; d1++) {
                    go = true, b = par[b];
                }
                for(; d2 < lowest_depth[b]; d2++) {
                    go = true, a = par[a];
                }
            }
            ans = (isAnc(a, b) || isAnc(b, a));
        }
        cout << (ans ? "YES" : "NO") << '\n';
        for(int i = 0; i < n; i++) {
            g[i].clear();
        }
    }
}