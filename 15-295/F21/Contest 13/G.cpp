#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, x_1, x_2, y_1, y_2, cur, in[15001], ans;
pair<int, int> polygon[15000];
vector<pair<int, int>> vertical_segments[15001];

int main() {
    cin >> x_1 >> y_1 >> x_2 >> y_2 >> n;
    swap(y_1, y_2);
    for(int i = 0; i < n; i++) {
        cin >> polygon[i].f >> polygon[i].s;
    }
    for(int i = 0; i < n; i++) {
        if(polygon[i].f == polygon[(i + 1) % n].f) {
            vertical_segments[polygon[i].f].push_back({polygon[i].s, polygon[(i + 1) % n].s});
        }
    }
    for(int i = 0; i < x_2; i++) {
        for(pair<int, int> vs: vertical_segments[i]) {
            int ep1 = max(y_1, min(vs.f, vs.s));
            int ep2 = min(y_2, max(vs.f, vs.s));
            if(ep1 >= ep2) {
                continue;
            }
            int pv = cur;
            cur += (in[ep1] ^ 1) - in[ep1];
            cur += (in[ep2] ^ 1) - in[ep2];
            in[ep1] ^= 1, in[ep2] ^= 1;
            if(i > x_1 && vs.f > vs.s) {
                ans += (cur - pv) / 2;
            }
        }
        if(i == x_1) {
            ans += cur / 2;
        }
    }
    cout << ans << endl;
}
