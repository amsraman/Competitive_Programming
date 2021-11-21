#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> g[20], ord[20];

void dfs(int u) {
    if(u > 0) {
        ord[u].push_back(u + 1);
    }
    vector<int> mrg[2];
    for(int i = 0; i < (int) g[u].size(); i++) {
        dfs(g[u][i]);
        mrg[i & 1].clear();
        for(int v: mrg[i & 1 ^ 1]) {
            mrg[i & 1].push_back(v);
        }
        for(int j = 0; j < ord[g[u][i]].size(); j++) {
            mrg[i & 1].push_back(ord[g[u][i]][j]);
            if(j & 1) {
                for(int k = 0; k < mrg[i & 1 ^ 1].size(); k++) {
                    mrg[i & 1].push_back(mrg[i & 1 ^ 1][k]);
                }
            } else {
                for(int k = mrg[i & 1 ^ 1].size() - 1; k >= 0; k--) {
                    mrg[i & 1].push_back(mrg[i & 1 ^ 1][k]);
                }
            }
        }
    }
    for(int v: mrg[(g[u].size()) & 1 ^ 1]) {
        ord[u].push_back(v);
    }
}

int main() {
    cin >> n;
    for(int i = 0, p; i < n - 1; i++) {
        cin >> p;
        g[p - 1].push_back(i + 1);
    }
    dfs(0);
    cout << ord[0].size() << endl;
    for(int i: ord[0]) {
        cout << i << " ";
    }
    cout << endl;
}