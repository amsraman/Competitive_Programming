#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

const ld epsilon = 1e-6;

int n;
array<ld, 3> b, s, p, d;
bool ans = true;

ld point_to_point(array<ld, 3> p1, array<ld, 3> p2) {
    array<ld, 3> df = {p1[0] - p2[0], p1[1] - p2[1], p1[2] - p2[2]};
    return sqrt(df[0] * df[0] + df[1] * df[1] + df[2] * df[2]);
}

ld point_to_seg(array<ld, 3> p, array<ld, 3> ep1, array<ld, 3> ep2) {
    array<ld, 3> df = {ep2[0] - ep1[0], ep2[1] - ep1[1], ep2[2] - ep1[2]};
    ld lb = 0, ub = 1;
    while(ub - lb > 1e-12) {
        ld m1 = (2 * lb + ub) / 3, m2 = (lb + 2 * ub) / 3;
        array<ld, 3> p1 = {ep1[0] + m1 * df[0], ep1[1] + m1 * df[1], ep1[2] + m1 * df[2]};
        array<ld, 3> p2 = {ep1[0] + m2 * df[0], ep1[1] + m2 * df[1], ep1[2] + m2 * df[2]};
        if(point_to_point(p, p1) > point_to_point(p, p2)) {
            lb = m1;
        } else {
            ub = m2;
        }
    }
    array<ld, 3> pt = {ep1[0] + ub * df[0], ep1[1] + ub * df[1], ep1[2] + ub * df[2]};
    return point_to_point(p, pt);
}

ld seg_dist(array<ld, 3> ep1, array<ld, 3> ep2) {
    array<ld, 3> df = {s[0] - b[0], s[1] - b[1], s[2] - b[2]};
    ld lb = 0, ub = 1;
    while(ub - lb > epsilon) {
        ld m1 = (2 * lb + ub) / 3, m2 = (lb + 2 * ub) / 3;
        array<ld, 3> p1 = {b[0] + m1 * df[0], b[1] + m1 * df[1], b[2] + m1 * df[2]};
        array<ld, 3> p2 = {b[0] + m2 * df[0], b[1] + m2 * df[1], b[2] + m2 * df[2]};
        if(point_to_seg(p1, ep1, ep2) > point_to_seg(p2, ep1, ep2)) {
            lb = m1;
        } else {
            ub = m2;
        }
    }
    array<ld, 3> pt = {b[0] + ub * df[0], b[1] + ub * df[1], b[2] + ub * df[2]};
    return point_to_seg(pt, ep1, ep2);
}

int main() {
    cin >> b[0] >> b[1] >> b[2] >> s[0] >> s[1] >> s[2] >> n;
    for(int i = 0, m; i < n; i++) {
        cin >> p[0] >> p[1] >> p[2] >> d[0] >> d[1] >> d[2] >> m;
        ld mx_rad = 0;
        for(int j = 0; j < m; j++) {
            array<ld, 3> point;
            cin >> point[0] >> point[1] >> point[2];
            ld rad = point_to_point(p, point);
            mx_rad = max(mx_rad, rad);
        }
        array<ld, 3> ep = {p[0] + d[0] * 3e6, p[1] + d[1] * 3e6, p[2] + d[2] * 3e6};
        if(seg_dist(p, ep) < mx_rad + epsilon) {
            ans = false;
        }
    }
    cout << (ans ? "Go" : "Surrender") << endl;
}