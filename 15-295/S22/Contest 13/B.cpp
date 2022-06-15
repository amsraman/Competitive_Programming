#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n;
pair<int, int> poly[100];

int cross(int fx, int fy, int sx, int sy) {
    return fx * sy - fy * sx;
}

int turn(int i, int j, int k) {
    return cross(poly[j].f - poly[i].f, poly[j].s - poly[i].s, poly[k].f - poly[j].f, poly[k].s - poly[j].s);
}

int area(int i, int j, int k) {
    int s1 = poly[i].f * poly[j].s + poly[j].f * poly[k].s + poly[k].f * poly[i].s;
    int s2 = poly[i].s * poly[j].f + poly[j].s * poly[k].f + poly[k].s * poly[i].f;
    return abs(s1 - s2);
}

long double dist(int i, int j) {
    int dx = poly[i].f - poly[j].f, dy = poly[i].s - poly[j].s;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int _ = 1; n > 0; _++) {
        for(int i = 0; i < n; i++) {
            cin >> poly[i].f >> poly[i].s;
        }
        long double ans = 1e5;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                bool ok = true;
                int sgn = 0;
                for(int k = 0; k < n; k++) {
                    int tn = turn(i, k, j);
                    if(tn == 0) {
                        continue;
                    }
                    tn /= abs(tn);
                    if(sgn == 0) {
                        sgn = tn;
                    } else if(tn != sgn) {
                        ok = false;
                    }
                }
                if(!ok) {
                    continue;
                }
                long double cur = 0, d = dist(i, j);
                for(int k = 0; k < n; k++) {
                    cur = max(cur, (long double) area(i, j, k) / d);
                }
                ans = min(ans, cur);
            }
        }
        cout << "Case " << _ << ": " << fixed << setprecision(2) << ans << endl;
        cin >> n;
    }
}