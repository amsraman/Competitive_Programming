#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 1e9 + 7;

int main() {
    ifstream cin("circular_circles_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m, e, k; cin >> n >> m >> e >> k;
        vector<int> x(n), y(n), edge_id(e), wt(e);
        for(int i = 0; i < k; i++) cin >> x[i];
        int ax, bx, cx; cin >> ax >> bx >> cx;
        for(int i = 0; i < k; i++) cin >> y[i];
        int ay, by, cy; cin >> ay >> by >> cy;
        for(int i = 0; i < k; i++) cin >> edge_id[i];
        int ai, bi, ci; cin >> ai >> bi >> ci;
        for(int i = 0; i < k; i++) cin >> wt[i];
        int aw, bw, cw; cin >> aw >> bw >> cw;
        for(int i = k; i < n; i++) {
            x[i] = (1LL * ax * x[i - 2] + 1LL * bx * x[i - 1] + cx) % m;
            y[i] = (1LL * ay * y[i - 2] + 1LL * by * y[i - 1] + cy) % m;
        }
        for(int i = k; i < e; i++) {
            edge_id[i] = (1LL * ai * edge_id[i - 2] + 1LL * bi * edge_id[i - 1] + ci) % (n * m + n);
            wt[i] = (1LL * aw * wt[i - 2] + 1LL * bw * wt[i - 1] + cw) % int(1e9);
        }
        vector<int> edge_wts(n * m + n, 1);
        vector<array<multiset<int>, 2>> wts(n); multiset<int> cands;
        for(int i = 0; i < n; i++) {
            int fst = x[i], snd = y[i];
            if(fst > snd) swap(fst, snd);
            for(int j = 0; j < snd - fst; j++) wts[i][0].insert(1);
            for(int j = 0; j < m - (snd - fst); j++) wts[i][1].insert(1);
            wts[i][0].insert(-1e9); wts[i][1].insert(-1e9);
            cands.insert(1); cands.insert(min(*--wts[i][0].end(), *--wts[i][1].end()));
        }
        int ans = 1; ll tot = n * m + n, circle_sum = n;
        for(int i = 0; i < e; i++) {
            if(edge_id[i] >= n * m) {
                cands.erase(cands.find(edge_wts[edge_id[i]]));
                cands.insert(wt[i]);
            } else {
                int circ = edge_id[i] / m, fst = x[circ], snd = y[circ], vert = edge_id[i] % m;
                if(fst > snd) swap(fst, snd);
                circle_sum -= max(*--wts[circ][0].end(), *--wts[circ][1].end());
                cands.erase(cands.find(min(*--wts[circ][0].end(), *--wts[circ][1].end())));
                if(fst <= vert && vert < snd) {
                    wts[circ][0].erase(wts[circ][0].find(edge_wts[edge_id[i]]));
                    wts[circ][0].insert(wt[i]);
                } else {
                    wts[circ][1].erase(wts[circ][1].find(edge_wts[edge_id[i]]));
                    wts[circ][1].insert(wt[i]);
                }
                cands.insert(min(*--wts[circ][0].end(), *--wts[circ][1].end()));
                circle_sum += max(*--wts[circ][0].end(), *--wts[circ][1].end());
            }
            tot += wt[i] - edge_wts[edge_id[i]];
            edge_wts[edge_id[i]] = wt[i];
            int res = (tot - circle_sum - *--cands.end()) % mod;
            ans = (1LL * ans * res) % mod;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}