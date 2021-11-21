#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define f first
#define s second

using namespace std;

int t, n;
pair<int, int> points[300], blue;

ld dist(pair<ld, ld> p1, pair<ld, ld> p2) {
    return sqrt((p2.f - p1.f) * (p2.f - p1.f) + (p2.s - p1.s) * (p2.s - p1.s));
}

ll cross(pair<int, int> p1, pair<int, int> p2) {
    return (ll) p1.f * p2.s - (ll) p1.s * p2.f;
}

ll side(pair<int, int> p1, pair<int, int> p2, pair<int, int> q) {
    return cross({q.f - p1.f, q.s - p1.s}, {p2.f - q.f, p2.s - q.s});
}

bool same_side(ll c1, ll c2) {
    if(c1 < 0 && c2 < 0) {
        return true;
    }
    if(c1 > 0 && c2 > 0) {
        return true;
    }
    return false;
}

bool in_triangle(int p1, int p2, int p3) {
    ll sd1 = side(points[p1], points[p2], blue);
    ll sd2 = side(points[p1], points[p2], points[p3]);
    if(!same_side(sd1, sd2)) {
        return false;
    }
    sd1 = side(points[p2], points[p3], blue);
    sd2 = side(points[p2], points[p3], points[p1]);
    if(!same_side(sd1, sd2)) {
        return false;
    }
    sd1 = side(points[p1], points[p3], blue);
    sd2 = side(points[p1], points[p3], points[p2]);
    if(!same_side(sd1, sd2)) {
        return false;
    }
    return true;
}

bool in_segment(int p1, int p2) {
    if(blue.f <= min(points[p1].f, points[p2].f) || blue.f >= max(points[p1].f, points[p2].f)) {
        return false;
    }
    return side(points[p1], points[p2], blue) == 0;
}

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> points[i].f >> points[i].s;
        }
        cin >> blue.f >> blue.s;
        ld ans = 5e6;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                for(int k = j + 1; k < n; k++) {
                    if(in_triangle(i, j, k)) {
                        ans = min(ans, dist(points[i], points[j]) + dist(points[j], points[k]) + dist(points[i], points[k]));
                    }
                }
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(in_segment(i, j)) {
                    ld s1 = 4e6, s2 = 4e6;
                    for(int k = 0; k < n; k++) {
                        if(k != i && k != j && side(points[i], points[j], points[k]) < 0) {
                            s1 = min(s1, dist(points[i], points[k]) + dist(points[j], points[k]));
                        }
                        if(k != i && k != j && side(points[i], points[j], points[k]) > 0) {
                            s2 = min(s2, dist(points[i], points[k]) + dist(points[j], points[k]));
                        }
                    }
                    ans = min(ans, s1 + s2);
                }
            }
        }
        cout << "Case #" << _ << ": ";
        if(ans == 5e6) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << fixed << setprecision(7) << ans << endl;
        }
    }
}