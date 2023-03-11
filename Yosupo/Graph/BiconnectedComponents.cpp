// 649 ms
#include <bits/stdc++.h>

using namespace std;

struct TarjanBCC {
    int n, time = 0, bcc_count = 0, cut_count = 0;
    vector<int> in, lp, bcc;
    vector<bool> cut;
    stack<pair<int, int>> dfs_stack;
    vector<vector<int>> graph, comp_vertices;
    vector<vector<pair<int, int>>> comp_edges;
    int dfs(int u, int p = -1) {
        in[u] = lp[u] = ++time;
        int ch = 0; pair<int, int> lst_edge;
        for(int v: graph[u]) {
            if(in[v] == -1) {
                ++ch; dfs_stack.emplace(u, v);
                lp[u] = min(lp[u], dfs(v, u));
                if(lp[v] >= in[u]) {
                    if(p != -1 && !cut[u]) cut[u] = true, bcc[u] = bcc_count++, cut_count++;
                    bcc_count++;
                    do {
                        comp_edges[bcc_count - 1].emplace_back(lst_edge = dfs_stack.top()); dfs_stack.pop();
                    } while(lst_edge != make_pair(u, v));
                }
            } else if(v != p && in[v] < in[u]) {
                lp[u] = min(lp[u], in[v]), dfs_stack.emplace(u, v);
            }
        }
        if(p == -1 && ch != 1) {
            if(ch == 0) comp_vertices[bcc_count].push_back(u);
            else cut[u] = true, ++cut_count;
            bcc[u] = bcc_count++;
        }
        return lp[u];
    }
    TarjanBCC(const vector<vector<int>> & graph): n((int) graph.size()), in(n, -1), lp(n), bcc(n, -1), cut(n, false), graph(graph), comp_edges(2 * n), comp_vertices(3 * n) {
        for(int i = 0; i < n; i++) {
            if(in[i] == -1) {
                dfs(i);
            }
        }
        comp_edges.resize(bcc_count); comp_vertices.resize(bcc_count);
        vector<bool> vis(n, false);
        for(int i = 0; i < bcc_count; i++) {
            for(auto [u, v]: comp_edges[i]) {
                if(!vis[u]) {
                    if(!cut[u]) bcc[u] = i;
                    comp_vertices[i].push_back(u), vis[u] = true;
                }
                if(!vis[v]) {
                    if(!cut[v]) bcc[v] = i;
                    comp_vertices[i].push_back(v), vis[v] = true;
                }
            }
            for(auto [u, v]: comp_edges[i]) vis[u] = vis[v] = false;
        }
    }
    vector<vector<int>> block_cut_forest() {
        vector<vector<int>> res(bcc_count);
        for(int i = 0; i < bcc_count; i++) {
            for(int u: comp_vertices[i]) {
                if(cut[u]) {
                    res[bcc[u]].push_back(i);
                    res[i].push_back(bcc[u]);
                }
            }
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        g[a].push_back(b), g[b].push_back(a);
    }
    TarjanBCC bcc(g);
    cout << bcc.bcc_count - bcc.cut_count << '\n';
    for(auto comp: bcc.comp_vertices) {
        if(comp.empty()) continue;
        cout << comp.size() << " ";
        for(auto v: comp) {
            cout << v << " ";
        }
        cout << '\n';
    }
}