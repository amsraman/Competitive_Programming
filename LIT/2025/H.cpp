#include <bits/stdc++.h>

using namespace std;

vector<int> dominator_tree(const vector<vector<int>> & graph, int source) {
    int n = graph.size();
    vector<int> ord, in(n, -1), par(n), mn(n), link(n), sdom(n), dom(n, -1);
    iota(mn.begin(), mn.end(), 0), iota(link.begin(), link.end(), 0), iota(sdom.begin(), sdom.end(), 0);
    vector<vector<int>> reverse_graph(n), bucket(n);
    auto dfs = [&](auto rec, int u) -> void {
        in[u] = ord.size(); ord.push_back(u);
        for(int v: graph[u]) {
            if(in[v] == -1) {
                par[v] = u;
                rec(rec, v);
            }
            reverse_graph[v].push_back(u);
        }
    };
    auto dfs_cmp = [&](int u, int v) {
        return in[u] < in[v];
    };
    auto find = [&](auto rec, int u) -> int {
        if(link[u] != u) {
            int v = rec(rec, link[u]);
            link[u] = link[link[u]];
            if(dfs_cmp(sdom[v], sdom[mn[u]])) mn[u] = v;
        }
        return mn[u];
    };
    dfs(dfs, source);
    reverse(ord.begin(), ord.end());
    for(int u: ord) {
        for(int v: reverse_graph[u]) {
            if(in[v] != -1) {
                int w = find(find, v);
                if(dfs_cmp(sdom[w], sdom[u])) sdom[u] = sdom[w]; 
            }
        }
        if(u != source) bucket[sdom[u]].push_back(u);
        for(int v: bucket[u]) {
            int w = find(find, v);
            dom[v] = sdom[v] == sdom[w] ? sdom[v] : w;
        }
        for(int v: graph[u]) {
            if(par[v] == u) link[v] = u;
        }
    }
    ord.pop_back(); reverse(ord.begin(), ord.end());
    for(int u: ord) {
        if(dom[u] != sdom[u]) dom[u] = dom[dom[u]];
    }
    return dom;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> ord, begin_point(n);
    for(int step = 1; step <= n; step++) {
        begin_point[step - 1] = (int) ord.size();
        for(int i = step - 1; i < n; i += step) {
            ord.push_back(i);
        }
    }
    int p2 = 1;
    while(p2 < (int) ord.size()) p2 <<= 1;
    vector<vector<int>> g(4 * p2 + n + m);
    for(int i = 0; i < (int) ord.size(); i++) {
        g[n + p2 + i].push_back(ord[i]);
        g[ord[i]].push_back(n + 3 * p2 + i);
    }
    for(int i = p2 - 1; i > 0; i--) {
        g[n + i].push_back(n + 2 * i);
        g[n + i].push_back(n + 2 * i + 1);
        g[n + 2 * p2 + 2 * i].push_back(n + 2 * p2 + i);
        g[n + 2 * p2 + 2 * i + 1].push_back(n + 2 * p2 + i);
    }
    auto get_range = [&](int l, int r, int step) {
        return make_pair(begin_point[step - 1] + l / step - 1, begin_point[step - 1] + r / step - 1);
    };
    for(int i = 0, a1, l1, r1, a2, l2, r2; i < m; i++) {
        cin >> a1 >> l1 >> r1 >> a2 >> l2 >> r2;
        l1 = (l1 + a1 - 1) / a1 * a1, l2 = (l2 + a2 - 1) / a2 * a2;
        r1 = r1 / a1 * a1, r2 = r2 / a2 * a2;
        if(l1 > r1 || l2 > r2) continue;
        auto [lo1, hi1] = get_range(l1, r1, a1);
        for(int lo = lo1 + p2, hi = hi1 + p2; lo <= hi; lo >>= 1, hi >>= 1) { // this node goes into some inputs
            if(lo & 1) g[n + 4 * p2 + i].push_back(n + lo++);
            if(hi & 1 ^ 1) g[n + 4 * p2 + i].push_back(n + hi--);
        }
        auto [lo2, hi2] = get_range(l2, r2, a2);
        for(int lo = lo2 + p2, hi = hi2 + p2; lo <= hi; lo >>= 1, hi >>= 1) { // some outputs go into this node
            if(lo & 1) g[n + 2 * p2 + lo++].push_back(n + 4 * p2 + i);
            if(hi & 1 ^ 1) g[n + 2 * p2 + hi--].push_back(n + 4 * p2 + i);
        }
    }
    int dest, q; cin >> dest >> q; --dest;
    auto dom = dominator_tree(g, dest);
    vector<vector<int>> dom_g((int) dom.size()); vector<int> id((int) dom.size(), -1);
    for(int i = 0; i < (int) dom.size(); i++) {
        if(dom[i] != -1) dom_g[dom[i]].push_back(i);
    }
    auto dfs = [&](auto rec, int u) -> void {
        if(id[u] == 0 && u >= n + 4 * p2) id[u] = u + 1;
        for(int v: dom_g[u]) {
            id[v] = id[u];
            rec(rec, v);
        }
    };
    id[dest] = 0;
    dfs(dfs, dest);
    for(int i = 0, x, y; i < q; i++) {
        cin >> x >> y; --x, --y;
        if(id[x] == -1 || id[y] == -1 || (id[x] != 0 && id[x] == id[y])) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
        }
    }
}