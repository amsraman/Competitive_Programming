#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n;
vector<int> g[500000], nums;
pair<int, int> in[500000];

void dfs(int x, int p) {
    for(int i: g[x]) {
        if(i != p) {
            dfs(i, x);
        }
    }
    nums.push_back(x);
    for(int i = g[x].size() - 1; i >= 0; i--) {
        if(g[x][i] != p) {
            nums.push_back(g[x][i]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }
    for(int i = 0; i < n; i++) {
        in[i] = {-1, -1};
    }
    dfs(0, 0);
    nums.push_back(0);
    for(int i = 0; i < 2 * n; i++) {
        if(in[nums[i]].f == -1) {
            in[nums[i]].f = i + 1;
        } else {
            in[nums[i]].s = i + 1;
        }
    }
    for(int i = 0; i < n; i++) {
        cout << in[i].f << " " << in[i].s << '\n';
    }
    for(int i = 0; i < n; i++) {
        for(int j: g[i]) {
            assert(in[j].f <= in[i].s && in[j].s >= in[i].f);
        }
    }
}