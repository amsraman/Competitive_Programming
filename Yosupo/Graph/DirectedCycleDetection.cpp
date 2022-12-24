// 267 ms
#include <bits/stdc++.h>

using namespace std;

int n, m;
stack<int> edge_stack;
vector<int> cycle;
vector<pair<int, int>> edges;
vector<vector<pair<int, int>>> graph;
vector<bool> vis, fin;

void dfs(int u) {
    vis[u] = true;
    for(pair<int, int> e: graph[u]) {
        if(!vis[e.first]) {
            edge_stack.push(e.second);
            dfs(e.first);
            if(!edge_stack.empty() && e.second == edge_stack.top()) {
                edge_stack.pop();
            }
        } else if(!fin[e.first] && cycle.empty()) {
            while(true) {
                cycle.push_back(edge_stack.top()); edge_stack.pop();
                if(edges[cycle.back()].first == e.first || edges[cycle.back()].second == e.first) {
                    break;
                }
            }
            reverse(cycle.begin(), cycle.end()), cycle.push_back(e.second);
        }
    }
    fin[u] = true;
}

int main() {
    cin >> n >> m;
    graph.resize(n), vis.resize(n, false), fin.resize(n, false);
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        graph[u].push_back({v, i});
        edges.push_back({u, v});
    }
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    if(!cycle.empty()) {
        cout << cycle.size() << '\n';
        for(int e: cycle) {
            cout << e << '\n';
        }
    } else {
        cout << "-1\n";
    }
}