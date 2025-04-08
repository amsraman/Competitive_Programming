#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<pair<int, int>> pts;
    for(int i = 0, x, y; i < n; i++) {
        cin >> x >> y; pts.emplace_back(x, y);
    }
    vector<vector<int>> g(n);
    vector<pair<int, int>> edges; vector<int> edge_to, edge_wt;
    for(int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w; --u, --v; edges.emplace_back(u, v);
        edge_to.push_back(v); edge_to.push_back(u); edge_wt.push_back(w);
        g[u].push_back(2 * i); g[v].push_back(2 * i + 1);
    }
    int s; char d; cin >> s >> d; --s;
    string dirs = "SWNE";
    auto get_dir = [&](int x, int y) {
        if(pts[x].first == pts[y].first) {
            return pts[x].second > pts[y].second ? 0 : 2;
        }
        return pts[x].first < pts[y].first ? 3 : 1;
    };
    auto get_next = [&](int vertex, int edge) {
        int sz = (int) g[vertex].size(), pos = 0;
        if(sz == 1) return -1;
        while(g[vertex][pos] != (edge ^ 1)) ++pos;
        return g[vertex][(pos + (sz / 2)) % sz];
    };
    auto remove_edge = [&](int edge) {
        auto [u, v] = edges[edge];
        for(int it = 0; it < 2; it++) {
            int pos = 0;
            while(g[u][pos] != 2 * edge + it) ++pos;
            g[u].erase(g[u].begin() + pos);
            swap(u, v);
        }
    };
    for(int i = 0; i < n; i++) {
        sort(g[i].begin(), g[i].end(), [&](int x, int y) {
            return get_dir(i, edge_to[x]) < get_dir(i, edge_to[y]);
        });
    }
    int cur_vertex = s, cur_edge = 0;
    while(dirs[get_dir(cur_vertex, edge_to[g[cur_vertex][cur_edge]])] != d) ++cur_edge;
    cur_edge = g[cur_vertex][cur_edge];
    vector<bool> seen(2 * m, false); vector<int> edges_on_path; edges_on_path.push_back(cur_edge); seen[cur_edge] = true;
    vector<int> both_seen(m, 0); ++both_seen[cur_edge / 2];
    while(true) {
        int nxt_vertex = edge_to[cur_edge];
        int nxt_edge = get_next(nxt_vertex, cur_edge);
        if(nxt_edge == -1) {
            cur_vertex = nxt_vertex;
            break;
        }
        if(edge_wt[cur_edge / 2] == both_seen[cur_edge / 2]) {
            for(int edge: edges_on_path) {
                --edge_wt[edge / 2]; --both_seen[edge / 2]; seen[edge] = false;
            }
            remove_edge(cur_edge / 2); edges_on_path.clear();
        }
        if(seen[nxt_edge]) {
            int mn_occ = 1e9;
            for(int i = (int) edges_on_path.size() - 1; i >= 0; i--) {
                mn_occ = min(mn_occ, (edge_wt[edges_on_path[i] / 2] - 1) / both_seen[edges_on_path[i] / 2]);
                if(edges_on_path[i] == nxt_edge) {
                    break;
                }
            }
            while(true) {
                int edge_to_pop = edges_on_path.back(); edges_on_path.pop_back();
                seen[edge_to_pop] = false; --both_seen[edge_to_pop / 2]; edge_wt[edge_to_pop / 2] -= mn_occ;
                if(edge_to_pop == nxt_edge) break;
            }
        }
        edges_on_path.push_back(nxt_edge); seen[nxt_edge] = true; ++both_seen[nxt_edge / 2];
        tie(cur_vertex, cur_edge) = make_pair(nxt_vertex, nxt_edge);
    }
    cout << pts[cur_vertex].first << " " << pts[cur_vertex].second << '\n';
}