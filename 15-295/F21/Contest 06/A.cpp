#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, lst[100000];
long long dist[100000];
vector<pair<int, int>> g[100000];

int main() {
    cin >> n >> m;
    for(int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        g[u - 1].push_back({v - 1, w});
        g[v - 1].push_back({u - 1, w});
    }
    for(int i = 1; i < n; i++) {
        dist[i] = 1e15;
    }
    priority_queue<pair<long long, int>> q;
    q.push({0, 0});
    while(!q.empty()) {
        long long x = q.top().f;
        int y = q.top().s;
        q.pop();
        if(-x > dist[y]) {
            continue;
        }
        for(pair<int, int> i: g[y]) {
            if(dist[y] + i.s < dist[i.f]) {
                dist[i.f] = dist[y] + i.s;
                q.push({-dist[i.f], i.f});
                lst[i.f] = y;
            }
        }
    }
    if(dist[n - 1] == 1e15) {
        cout << -1 << endl;
    } else {
        vector<int> path;
        int cur = n - 1;
        path.push_back(cur);
        while(cur > 0) {
            cur = lst[cur];
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());
        for(int i: path) {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
}