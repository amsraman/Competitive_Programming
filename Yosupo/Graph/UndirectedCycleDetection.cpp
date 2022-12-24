// 468 ms
#include <bits/stdc++.h>

using namespace std;

int n, m;
stack<int> edge_stack;
vector<int> cycle_vertices, cycle;
vector<pair<int, int>> edges;
vector<vector<pair<int, int>>> graph;
vector<bool> vis;

void dfs(int u, int pv_edge = -1) {
    vis[u] = true;
    for(pair<int, int> e: graph[u]) {
        if(!vis[e.first]) {
            edge_stack.push(e.second);
            dfs(e.first, e.second);
            if(!edge_stack.empty() && e.second == edge_stack.top()) {
                edge_stack.pop();
            }
        } else if(e.second != pv_edge && cycle.empty()) {
            cycle_vertices.push_back(u);
            while(!edge_stack.empty()) {
                int cur_edge = edge_stack.top();
                cycle_vertices.push_back(edges[cur_edge].first ^ edges[cur_edge].second ^ cycle_vertices.back());
                cycle.push_back(cur_edge); edge_stack.pop();
                if(edges[cur_edge].first == e.first || edges[cur_edge].second == e.first) {
                    break;
                }
            }
            cycle.push_back(e.second);
        }
    }
}

int main() {
    cin >> n >> m;
    graph.resize(n), vis.resize(n, false);
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
        edges.push_back({u, v});
    }
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    if(!cycle.empty()) {
        cout << cycle.size() << '\n';
        for(int v: cycle_vertices) {
            cout << v << ' ';
        }
        cout << '\n';
        for(int e: cycle) {
            cout << e << ' ';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
    }
}