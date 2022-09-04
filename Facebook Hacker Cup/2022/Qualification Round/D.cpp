#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef long long ll;
#define f first
#define s second

using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    ifstream cin("second_flight_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<int> deg(n, 0);
        vector<pair<int, int>> qrs(q);
        vector<unordered_set<int>> adj(n);
        vector<gp_hash_table<int, int, custom_hash>> wt(n);
        vector<gp_hash_table<int, ll, custom_hash>> val(n);
        for(int i = 0, a, b, c; i < m; i++) {
            cin >> a >> b >> c;
            adj[a - 1].insert(b - 1); ++deg[a - 1];
            adj[b - 1].insert(a - 1); ++deg[b - 1];
            wt[a - 1][b - 1] = wt[b - 1][a - 1] = c;
        }
        for(int i = 0, x, y; i < q; i++) {
            cin >> x >> y;
            if(x > y) swap(x, y);
            qrs[i] = {x - 1, y - 1};
            if(!adj[x - 1].count(y - 1)) {
                adj[x - 1].insert(y - 1);
                adj[y - 1].insert(x - 1);
            }
        }
        for(int i = 0; i < n; i++) {
            vector<int> bigger;
            for(int j: adj[i]) {
                if(deg[j] > deg[i] || (deg[j] == deg[i] && j > i)) {
                    bigger.push_back(j);
                }
            }
            for(int u: bigger) {
                for(int v: bigger) {
                    if(u > v && adj[u].count(v)) {
                        int v1 = i, v2 = u, v3 = v;
                        for(int j = 0; j < 3; j++) {
                            pair<int, int> cur = {min(v1, v2), max(v1, v2)};
                            val[cur.f][cur.s] += min(wt[v1][v3], wt[v2][v3]);
                            swap(v1, v2), swap(v2, v3);
                        }
                    }
                }
            }
        }
        cout << "Case #" << _ << ": ";
        for(pair<int, int> qr: qrs) {
            cout << val[qr.f][qr.s] + 2 * wt[qr.f][qr.s] << " ";
        }
        cout << '\n';
    }
}