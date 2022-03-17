#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

typedef complex<ld> cd;

int n, cx, cy, r;
ld area;
cd points[100];

ld triangle_area(cd a, cd b, cd c) {
    return (a.real() * b.imag() + b.real() * c.imag() + c.real() * a.imag() - a.imag() * b.real() - b.imag() * c.real() - c.imag() * a.real()) / 2.0;
}

int main() {
    cin >> cx >> cy >> r >> n;
    for(int i = 0, px, py; i < n; i++) {
        cin >> px >> py;
        points[i] = cd(px - cx, py - cy);
    }
    for(int i = 0; i < n; i++) {
        cd p1 = points[i], p2 = points[(i + 1) % n];
        cd q1 = (cd) 1 / p1, q2 = (cd) 1 / p2;
        if(conj(p1) * p2 == p1 * conj(p2)) {
            continue;
        }
        cd circumcenter = conj(p1 - p2) / (conj(p1) * p2 - p1 * conj(p2));
        area += triangle_area(0, q1, q2) - triangle_area(circumcenter, q1, q2) + arg(q2 / q1) * abs(circumcenter * circumcenter);
    }
    cout << fixed << setprecision(9) << area * r * r * r * r  << endl;
}