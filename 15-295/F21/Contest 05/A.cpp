#include <bits/stdc++.h>

using namespace std;

int n, nc, chn[400];
map<string, int> ind;
vector<int> g[400], topo;
bool vis[400];

string conv(string s) {
    string ret = "";
    for(char c: s) {
        ret += toupper(c);
    }
    return ret;
}

void dfs(int x) {
    vis[x] = true;
    for(int i: g[x]) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    topo.push_back(x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2 >> s2;
        s1 = conv(s1), s2 = conv(s2);
        if(!ind.count(s1)) {
            ind[s1] = nc++;
        }
        if(!ind.count(s2)) {
            ind[s2] = nc++;
        }
        g[ind[s1]].push_back(ind[s2]);
    }
    for(int i = 0; i < nc; i++) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    reverse(topo.begin(), topo.end());
    for(int i = 0; i < nc; i++) {
        chn[i] = 1;
    }
    int ans = 0;
    for(int i: topo) {
        for(int j: g[i]) {
            chn[j] = max(chn[j], chn[i] + 1);
        }
        ans = max(ans, chn[i]);
    }
    cout << ans << '\n';
}