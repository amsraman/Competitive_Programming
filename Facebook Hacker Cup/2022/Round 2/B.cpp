#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

int main() {
    ifstream cin("balance_sheet_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, k, ans = 0;
        cin >> n >> k;
        vector<int> coords;
        vector<ll> best;
        vector<array<int, 4>> clients(n);
        vector<vector<ll>> k_best(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 4; j++) {
                cin >> clients[i][j];
            }
            coords.push_back(clients[i][0]);
            coords.push_back(clients[i][1]);
        }
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        vector<vector<pair<int, int>>> in(coords.size()), out(coords.size());
        for(int i = 0; i < n; i++) {
            clients[i][0] = lower_bound(coords.begin(), coords.end(), clients[i][0]) - coords.begin();
            clients[i][1] = lower_bound(coords.begin(), coords.end(), clients[i][1]) - coords.begin();
            out[clients[i][0]].push_back({clients[i][2], i});
            in[clients[i][1]].push_back({clients[i][3], i});
        }
        auto merge = [&](vector<ll> & to, vector<ll> & from) {
            vector<ll> tmp;
            for(int i = 0, j = 0; (i < to.size() || j < from.size()); ) {
                if(j == from.size() || (i < to.size() && to[i] <= from[j])) {
                    tmp.push_back(to[i++]);
                } else {
                    tmp.push_back(from[j++]);
                }
            }
            int delta = (int) tmp.size() - k;
            if(delta > 0) {
                tmp.erase(tmp.begin(), tmp.begin() + delta);
            }
            to = tmp;
        };
        for(int i = 0; i < coords.size(); i++) {
            vector<ll> best_so_far;
            sort(in[i].begin(), in[i].end());
            sort(out[i].begin(), out[i].end());
            for(int p1 = 0, p2 = 0; p1 < out[i].size(); p1++) {
                int ind = out[i][p1].s;
                while(p2 < in[i].size() && clients[in[i][p2].s][3] < clients[ind][2]) {
                    merge(best_so_far, k_best[in[i][p2].s]);
                    ++p2;
                }
                k_best[ind].push_back(-clients[ind][2]);
                merge(k_best[ind], best_so_far);
                for(int j = 0; j < k_best[ind].size(); j++) {
                    k_best[ind][j] += clients[ind][2];
                }
                merge(best, k_best[ind]);
                for(int j = 0; j < k_best[ind].size(); j++) {
                    k_best[ind][j] -= clients[ind][3];
                }
            }
        }
        for(ll b: best) {
            ans = (1LL * ans + b) % mod;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}