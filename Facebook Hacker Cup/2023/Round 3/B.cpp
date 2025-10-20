#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("hash_slinger_input.txt");
    ofstream cout("output.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m; cin >> n >> m;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i]; a[i] %= m;
        }
        int len = 1;
        while(len < m) len <<= 1;
        vector<vector<int>> mn(n, vector<int>(len, n));
        for(int i = n - 1; i >= 0; i--) {
            int tot = 0;
            for(int j = i; j < n; j++) {
                tot = (tot + a[j]) % m;
                mn[i][tot] = min(mn[i][tot], j);
            }
            if(i < n - 1) {
                for(int j = 0; j < len; j++) {
                    mn[i][j] = min(mn[i][j], mn[i + 1][j]);
                }
            }
        }
        int ans = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        vector<int> dist(len, n);
        q.push({-1, 0}); dist[0] = -1;
        while(!q.empty()) {
            auto [ind, val] = q.top(); q.pop();
            if(ind > dist[val]) continue;
            ++ans;
            if(ind == n - 1) continue;
            for(int i = 0; i < len; i++) {
                if(mn[ind + 1][i] < dist[i ^ val]) {
                    dist[i ^ val] = mn[ind + 1][i];
                    q.push({dist[i ^ val], i ^ val});
                }
            }
        }
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}