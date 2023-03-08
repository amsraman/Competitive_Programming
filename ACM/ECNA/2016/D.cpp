#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, num = 0, tot = 0; cin >> n >> m;
    map<string, int> ind; ind["English"] = 0;
    for(int i = 0; i < n; i++) {
        string lang; cin >> lang;
        ind[lang] = i + 1;
    }
    vector<vector<pair<int, int>>> g(n + 1);
    for(int i = 0; i < m; i++) {
        string l1, l2; int cost; cin >> l1 >> l2 >> cost;
        g[ind[l1]].push_back({ind[l2], cost});
        g[ind[l2]].push_back({ind[l1], cost});
    }
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> q;
    vector<bool> vis(n + 1, false);
    q.push({0, 0, 0});
    while(!q.empty()) {
        int d = q.top()[0], c = q.top()[1], u = q.top()[2]; q.pop();
        if(vis[u]) continue;
        vis[u] = true, ++num, tot += c;
        for(pair<int, int> e: g[u]) {
            q.push({d + 1, e.second, e.first});
        }
    }
    if(num <= n) {
        cout << "Impossible\n";
    } else {
        cout << tot << '\n';
    }
}
