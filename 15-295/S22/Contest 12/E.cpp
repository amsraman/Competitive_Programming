#include <bits/stdc++.h>

using namespace std;

const int sq = 350;

int n, q, p[100000], rev[100000], skip[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        --p[i];
        rev[p[i]] = i;
    }
    for(int i = 0; i < n; i++) {
        skip[i] = i;
        for(int j = 0; j < sq; j++) {
            skip[i] = p[skip[i]];
        }
    }
    for(int i = 0, t; i < q; i++) {
        cin >> t;
        if(t == 1) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            swap(p[x], p[y]);
            swap(rev[p[x]], rev[p[y]]);
            skip[x] = x, skip[y] = y;
            for(int j = 0; j < sq; j++) {
                skip[x] = p[skip[x]], skip[y] = p[skip[y]];
            }
            int sx = skip[x], sy = skip[y];
            for(int j = 0, cx = x, cy = y; j < sq; j++) {
                skip[cx] = sx, skip[cy] = sy;
                sx = rev[sx], sy = rev[sy];
                cx = rev[cx], cy = rev[cy];
            }
        } else {
            int v, k;
            cin >> v >> k;
            --v;
            while(k >= sq) {
                v = skip[v];
                k -= sq;
            }
            for(int i = 0; i < k; i++) {
                v = p[v];
            }
            cout << v + 1 << '\n';
        }
    }
}