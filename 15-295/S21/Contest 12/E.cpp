#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Point {
    T x_val, y_val;
    Point operator+(Point & P) {
        return {x_val + P.x_val, y_val + P.y_val};
    }
    Point operator-(Point & P) {
        return {x_val - P.x_val, y_val - P.y_val};
    }
    bool operator<(const Point & P) {
        return tie(x_val, y_val) < tie(P.x_val, P.y_val);
    }
    bool operator==(const Point & P) {
        return tie(x_val, y_val) == tie(P.x_val, P.y_val);
    } 
    T inner(const Point & P) {
        return x_val * P.x_val + y_val * P.y_val;
    }
    long double norm() {
        return sqrt(inner(*this));
    }
    T cross(const Point & P) {
        return x_val * P.y_val - y_val * P.x_val;
    }
    int turn(const Point & P) { // 1 means ccw
        if(x_val * P.y_val > y_val * P.x_val) {
            return 1;
        } else if(x_val * P.y_val == y_val * P.x_val) {
            return 0;
        }
        return -1;
    }
};

template <typename T>
vector<Point<T>> ConvexHull(vector<Point<T>> points) {
    if(points.size() <= 1) {
        return points;
    }
    sort(points.begin(), points.end());
    vector<Point<double>> hull(points.size() + 1);
    int s = 0, t = 0;
    for(int it = 2; it--; s = --t, reverse(points.begin(), points.end())) {
        for(Point p: points) {
            while(t >= s + 2 && (hull[t - 1] - hull[t - 2]).turn(p - hull[t - 2]) <= 0) {
                t--;
            }
            hull[t++] = p;
        }
    }
    return {hull.begin(), hull.begin() + t - (t == 2 && hull[0] == hull[1])};
}

int main() {
    int n;
    vector<array<double, 3>> plane(3);
    array<double, 3> p;
    for(int i = 0; i < 3; i++) {
        cin >> plane[i][0] >> plane[i][1] >> plane[i][2];
    }
    cin >> p[0] >> p[1] >> p[2] >> n;
    vector<array<double, 3>> polyhedron(n);
    for(int i = 0; i < n; i++) {
        cin >> polyhedron[i][0] >> polyhedron[i][1] >> polyhedron[i][2];
    }
    for(int i = 0; i < 3; i++) {
        plane[1][i] -= plane[0][i], plane[2][i] -= plane[0][i];
    }
    double a = plane[1][1] * plane[2][2] - plane[1][2] * plane[2][1];
    double b = plane[1][2] * plane[2][0] - plane[1][0] * plane[2][2];
    double c = plane[1][0] * plane[2][1] - plane[1][1] * plane[2][0];
    double d = a * plane[0][0] + b * plane[0][1] + c * plane[0][2];
    vector<Point<double>> pts;
    auto basis_alter = [&](array<double, 3> pt) -> Point<double> {
        double x_val = pt[0] * plane[1][0] + pt[1] * plane[1][1] + pt[2] * plane[1][2];
        double y_val = pt[0] * plane[2][0] + pt[1] * plane[2][1] + pt[2] * plane[2][2];
        return {x_val, y_val};
    };
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 3; j++) {
            polyhedron[i][j] -= p[j];
        }
        double denom = a * polyhedron[i][0] + b * polyhedron[i][1] + c * polyhedron[i][2];
        if(denom == 0) {
            continue;
        }
        double t = (d - a * p[0] - b * p[1] - c * p[2]) / denom;
        if(t >= 1) {
            array<double, 3> proj_pt = {p[0] + t * polyhedron[i][0], p[1] + t * polyhedron[i][1], p[2] + t * polyhedron[i][2]};
            pts.push_back(basis_alter(proj_pt));
        }
    }
    vector<Point<double>> hull = ConvexHull(pts);
    double area = 0;
    for(int i = 0; i < hull.size(); i++) {
        area += hull[i].cross(hull[(i + 1) % hull.size()]);
    }
    area /= sqrt(a * a + b * b + c * c);
    cout << fixed << setprecision(9) << abs(area) / 2 << endl;
}