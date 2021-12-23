#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int INF = 0x3f3f3f3f;

int n, k, h[500001], s[500000], mn1[500000], mn2[500000], ans = INF;
vector<int> g[500000];
vector<pair<int, int>> ord, down[500000];
set<pair<int, int>> nodes_left;
multiset<int> miners;

void dfs(int x, int p) {
    for(int i: g[x]) {
        if(i != p) {
            mn1[i] = mn1[x], mn2[i] = mn2[x];
            if(h[i] < h[mn1[i]]) {
                mn2[i] = mn1[i];
                mn1[i] = i;
            } else if(h[i] <= h[mn2[i]] || mn1[i] == mn2[i]) {
                mn2[i] = i;
            }
            dfs(i, x);
        }
    }
    down[mn1[x]].push_back({h[mn2[x]], x});
    ord.push_back({h[mn1[x]], x});
    nodes_left.insert({h[mn1[x]], x});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    cin >> k;
    for(int i = 0; i < k; i++) {
        cin >> s[i];
        miners.insert(s[i]);
    }
    while(miners.size() < n) {
        miners.insert(0);
    }
    h[n] = INF, mn2[0] = n;
    dfs(0, 0);
    sort(ord.begin(), ord.end());
    for(pair<int, int> p: ord) {
        auto it = miners.upper_bound(p.f);
        if(it == miners.begin()) {
            continue;
        }
        miners.erase(miners.find(*(--it)));
        nodes_left.erase(p);
    }
    if(miners.empty()) {
        cout << 0 << '\n';
    } else {
        int tallest = *(--miners.end());
        for(int i = 0; i < n; i++) {
            sort(down[i].begin(), down[i].end());
            multiset<int> rem_miners;
            set<pair<int, int>> rem_nodes;
            for(pair<int, int> j: down[i]) {
                auto node_it = nodes_left.lower_bound({h[mn1[j.s]], j.s});
                if(node_it == nodes_left.end()) {
                    continue;
                }
                auto miner_it = miners.upper_bound(j.f);
                if(miner_it == miners.begin()) {
                    continue;
                }
                rem_miners.insert(*(--miner_it)), miners.erase(miner_it);
                rem_nodes.insert(*node_it), nodes_left.erase(node_it);
            }
            if(miners.empty()) {
                ans = min(ans, tallest - h[i]);
            }
            for(int j: rem_miners) {
                miners.insert(j);
            }
            for(pair<int, int> j: rem_nodes) {
                nodes_left.insert(j);
            }
        }
        cout << (ans == INF ? -1 : ans) << '\n';
    }
}