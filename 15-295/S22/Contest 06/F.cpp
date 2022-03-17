#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

int n, p[1000][1000];
ld ev[1000], prb[1000];
bool done[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> p[i][j];
        }
        prb[i] = 1.0;
    }
    int cur = n - 1;
    for(int i = 0; i < n; i++) {
        done[cur] = true;
        for(int j = 0; j < n; j++) {
            if(!done[j]) {
                ld cur_prb = (ld) p[j][cur] / 100.0;
                ev[j] += ev[cur] * prb[j] * cur_prb;
                prb[j] *= (1.0 - cur_prb);
            }
        }
        cur = -1;
        ld best;
        for(int j = 0; j < n; j++) {
            if(!done[j]) {
                ld cur_ev = (ev[j] + prb[j]) / (1 - prb[j]);
                if(cur == -1 || cur_ev < best) {
                    best = cur_ev;
                    cur = j;
                }
            }
        }
        ev[cur] = (ev[cur] + 1) / (1 - prb[cur]);
    }
    cout << fixed << setprecision(9) << ev[0] << '\n';
}