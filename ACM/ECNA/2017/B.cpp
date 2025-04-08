#include <bits/stdc++.h>

using namespace std;

using fl = long double;
const fl eps = 1e-9, PI = 4 * atanl(1.0);

template <typename T>
struct Point {
    T x, y;
    Point() {};
    Point(T x, T y): x(x), y(y) {};
    enum orientation {CW, CCW, STRAIGHT};
    Point operator+(const Point & P) {return {x + P.x, y + P.y};}
    Point operator-(const Point & P) {return {x - P.x, y - P.y};}
    Point operator*(T c) {return {x * c, y * c};}
    Point operator/(T c) {return {x / c, y / c};}
    bool operator<(const Point & P) const {return tie(x, y) < tie(P.x, P.y);}
    bool operator==(const Point & P) const {return tie(x, y) == tie(P.x, P.y);} 
    T inner(const Point & P) const {return x * P.x + y * P.y;}
    T norm() {return inner(*this);}
    long double abs() {return sqrt(inner(*this));}
    Point normalize() {return (*this) / abs();}
    T cross(const Point & P) {return x * P.y - y * P.x;}
    orientation turn(const Point & P) const {
        if(x * P.y > y * P.x + eps) {
            return CCW;
        } else if(x * P.y == y * P.x - eps) {
            return STRAIGHT;
        }
        return CW;
    }
    static bool arg_cmp(const Point & P1, const Point & P2, const Point base_line, const orientation dir) {
        if(P1 == P2) return false;
        bool p1_section = base_line.turn(P1) == dir || (base_line.turn(P1) == STRAIGHT && base_line.inner(P1) <= 0);
        bool p2_section = base_line.turn(P2) == dir || (base_line.turn(P2) == STRAIGHT && base_line.inner(P2) <= 0);
        if(p1_section ^ p2_section) {
            return p1_section;
        }
        return (P2.x == 0 && P2.y == 0) || P1.turn(P2) == dir;
    } // it's times like these that make me wish cpp had hofs :(
    template <class output_stream>
    friend output_stream &operator<<(output_stream & out, Point P) {
        return out << "(" << P.x << ", " << P.y << ")";
    }
};

template <class Point>
struct Segment {
    Point p1, p2;
	Segment() {};
	Segment(Point p1, Point p2): p1(p1), p2(p2) {};
    bool intersects(const Segment & S) {
        Point p11 = p1, p12 = p2, p21 = S.p1, p22 = S.p2;
        if((p21 - p11).turn(p12 - p21) == Point::STRAIGHT && (p11 - p21).turn(p22 - p11) == Point::STRAIGHT) {
            bool x_int = max(p11.x, p12.x) >= min(p21.x, p22.x) && max(p21.x, p22.x) >= min(p11.x, p12.x);
            bool y_int = max(p11.y, p12.y) >= min(p21.y, p22.y) && max(p21.y, p22.y) >= min(p11.y, p12.y);
            return x_int && y_int;
        }
        bool s1 = (p21 - p11).turn(p12 - p21) != (p22 - p11).turn(p12 - p22);
        bool s2 = (p11 - p21).turn(p22 - p11) != (p12 - p21).turn(p22 - p12);
        return s1 && s2;
    }
    optional<Point> intersection(Segment & S) {
        if(!intersects(S)) {
            return nullopt;
        }
        auto t = (S.p1 - p1).cross(S.p2 - S.p1) / (p2 - p1).cross(S.p2 - S.p1);
        return p1 * (1 - t) + p2 * t;
    }
    auto dist(Point & P) {
        Point d1 = P - p1, d2 = p2 - p1, proj = p1 + d2 * d1.inner(d2) / d2.norm();
        auto res = min((P - p1).abs(), (P - p2).abs());
        if((proj - p1).inner(p2 - proj) >= 0) {
            res = min(res, (P - proj).abs());
        }
        return res;
    }
    auto dist(Segment & S) {
        if(S.intersects(*this)) return 0;
        return min({S.dist(p1), S.dist(p2), dist(S.p1), dist(S.p2)});
    }
    template <class output_stream>
    friend output_stream &operator<<(output_stream & out, Segment S) {
        return out << "[" << S.p1 << ", " << S.p2 << "]";
    }
};

template <typename T, class Point>
struct Circle {
    Point center; T rad;
    Circle(Point center, T rad): center(center), rad(rad) {};
    auto arg(Point P) {
        P = P - center; auto ang = atan2l(P.y, P.x);
        return (ang < 0 ? ang + 2 * PI : ang);
    }
    bool contains_inside(Point P) {
        return (P - center).abs() + eps < rad;
    }
    bool contains_inside(Circle C) {
        return (center - C.center).abs() + rad < C.rad;
    }
    vector<Point> intersection(Segment<Point> L) {
        vector<Point> res;
        Point ab = (L.p2 - L.p1).normalize(), ac = center - L.p1, proj = L.p1 + ab * ac.inner(ab);
        auto dist_to_mid = (proj - center).abs();
        if(rad < dist_to_mid) return res;
        auto dev = sqrt(rad * rad - dist_to_mid * dist_to_mid);
        res.push_back(proj + ab * dev); res.push_back(proj - ab * dev);
        if(dev <= eps) res.pop_back();
        return res;
    }
    vector<Point> intersection(Circle C) {
        vector<Point> res;
        Point v = (C.center - center).normalize();
        auto center_dist = (C.center - center).abs();
        if(C.center == center) return res;
        auto dist_to_mid = rad * (rad * rad + center_dist * center_dist - C.rad * C.rad) / (2 * rad * center_dist);
        if(dist_to_mid > rad) return res;
        auto dev = sqrt(rad * rad - dist_to_mid * dist_to_mid);
        Point mid = center + v * dist_to_mid, ortho(v.y, -v.x);
        res.push_back(mid + ortho * dev); res.push_back(mid - ortho * dev);
        if((res[0] - center).turn(C.center - res[0]) != Point::CCW) swap(res[0], res[1]);
        if(dev <= eps) res.pop_back();
        return res;
    }
    vector<Segment<Point>> tangents(Circle C, bool internal) {
        vector<Segment<Point>> res;
        if(internal) C.rad *= -1;
        Point v = C.center - center, ortho(v.y, -v.x);
        T dif = rad - C.rad, norm = v.norm(), dev = norm - dif * dif;
        if(norm == 0 || dev < 0) return res;
        for(int sgn = -1; sgn <= 1; sgn += 2) {
            Point p = (v * dif + ortho * sqrt(dev) * sgn) / norm;
            res.emplace_back(center + p * rad, C.center + p * C.rad);
        }
        if(dev <= eps) res.pop_back();
        return res;
    }
    template <class output_stream>
    friend output_stream &operator<<(output_stream & out, Circle C) {
        return out << "[" << C.center << ", " << C.rad << "]";
    }
};

template <typename T>
vector<pair<Point<T>, int>> convex_hull(vector<pair<Point<T>, int>> points) {
    if(points.size() <= 1) {
        return points;
    }
    sort(points.begin(), points.end());
    vector<pair<Point<T>, int>> hull(points.size() + 2);
    int s = 0, t = 0;
    for(int it = 2; it--; s = --t, reverse(points.begin(), points.end())) {
        for(auto p: points) {
            while(t >= s + 2 && (hull[t - 1].first - hull[t - 2].first).turn(p.first - hull[t - 2].first) != Point<T>::CCW) {
                t--;
            }
            hull[t++] = p;
        }
    }
    return {hull.begin(), hull.begin() + t - (t == 2 && hull[0] == hull[1])};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<Circle<fl, Point<fl>>> circles;
    for(int i = 0; i < n; i++) {
        int x, y, r; cin >> x >> y >> r; r += 10;
        circles.emplace_back(Point<fl>(x, y), r);
    }
    vector<pair<Point<fl>, int>> pts;
    auto add = [&](Point<fl> p1, int ind) {
        for(int i = 0; i < n; i++) {
            if(circles[i].contains_inside(p1)) return;
        }
        pts.emplace_back(p1, ind);
    };
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            auto tans = circles[i].tangents(circles[j], false);
            for(auto seg: tans) {
                add(seg.p1, i);
                add(seg.p2, j);
            }
        }
    }
    auto hull = convex_hull(pts);
    fl ans = 0; int sz = (int) hull.size();
    for(int i = 0; i < sz; i++) {
        auto cur = hull[i], nxt = hull[(i + 1) % sz];
        if(cur.second == nxt.second) {
            int ind = cur.second;
            fl df = circles[ind].arg(nxt.first) - circles[ind].arg(cur.first);
            if(df < 0) df += 2 * PI;
            ans += circles[ind].rad * df;
        } else {
            ans += (nxt.first - cur.first).abs();
        }
    }
    if(sz == 0) {
        fl mx_rad = 0;
        for(int i = 0; i < n; i++) mx_rad = max(mx_rad, circles[i].rad);
        ans = 2 * mx_rad * PI;
    }
    cout << fixed << setprecision(9) << ans << '\n';
}