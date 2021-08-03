#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

const ld epsilon = 1e-9;

int n;
ld orientation, ans;

struct Point {
    ld x_val, y_val;
    bool operator==(const Point &P) const {
        return (x_val == P.x_val && y_val == P.y_val);
    }
    bool operator<(const Point &P) const {
        return (x_val < P.x_val || x_val == P.x_val && y_val < P.y_val);
    }
    Point operator+(Point &P) {
        return {x_val + P.x_val, y_val + P.y_val};
    }
    Point operator-(Point &P) {
        return {x_val - P.x_val, y_val - P.y_val};
    }
    Point operator*(const ld &S) {
        return {x_val * S, y_val * S};
    }
    ld norm() {
        return sqrt(x_val * x_val + y_val * y_val);
    }
    ld inner(const Point &P) {
        return x_val * P.x_val + y_val * P.y_val;
    }
    ld cross(const Point &P) {
        return x_val * P.y_val - y_val * P.x_val;
    }
    int turn(const Point &P) {
        if(abs(x_val * P.y_val - y_val * P.x_val) < epsilon) {
            return 0;
        } else if(x_val * P.y_val > y_val * P.x_val) {
            return 1;
        }
        return -1;
    }
} points[200000];

struct HalfPlane {
    Point pos, dir;
    ld angle;
    HalfPlane(const Point &P, const Point &Q) : pos(P), dir(Q) {
        angle = atan2l(Q.y_val, Q.x_val);
    }
    bool operator<(HalfPlane &H) {
        if(abs(angle - H.angle) > epsilon) {
            return angle < H.angle;
        }
        return (H.pos - pos).turn(dir) == 1;
    }
    bool operator==(HalfPlane &H) {
        return abs(angle - H.angle) < epsilon;
    }
    bool outside(Point P) {
        return dir.turn(P - pos) == -1;
    }
    Point intersection(HalfPlane &H) {
        ld alpha = (H.pos - pos).cross(H.dir) / dir.cross(H.dir);
        return (dir * alpha) + pos;
    }
};
vector<HalfPlane> sides;

int main() {
    cin >> n;
    for(int i = 0; i<n; i++) {
        cin >> points[i].x_val >> points[i].y_val;
    }
    for(int i = 0; i<n; i++) {
        orientation += points[i].turn(points[(i+1)%n]);
    }
    if(orientation < 0) {
        reverse(points,points+n);
    }
    for(int i = 0; i<n; i++) {
        HalfPlane H(points[i], points[(i+1)%n] - points[i]);
        sides.push_back(H);
    }
    sort(sides.begin(),sides.end());
    sides.erase(unique(sides.begin(),sides.end()),sides.end());
    deque<HalfPlane> hull;
    int len = 0;
    for(HalfPlane H: sides) {
        while(len > 1 && H.outside((hull[len-1]).intersection(hull[len-2]))) {
            hull.pop_back();
            --len;
        }
        while(len > 1 && H.outside(hull[0].intersection(hull[1]))) {
            hull.pop_front();
            --len;
        }
        hull.push_back(H);
        ++len;
    }
    while(len > 2 && hull[0].outside(hull[len-1].intersection(hull[len-2]))) {
        hull.pop_back();
        --len;
    }
    while(len > 2 && hull[len-1].outside(hull[0].intersection(hull[1]))) {
        hull.pop_front();
        --len;
    }
    vector<Point> center_points;
    for(int i = 0; i<len; i++) {
        center_points.push_back(hull[i].intersection(hull[(i+1)%len]));
    }
    for(int i = 0; i<len; i++) {
        ans += center_points[i].cross(center_points[(i+1)%len]);
    }
    cout << fixed << setprecision(9) << abs(ans / 2.0) << endl;
}