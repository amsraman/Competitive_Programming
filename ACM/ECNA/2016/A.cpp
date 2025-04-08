#include <bits/stdc++.h>

using namespace std;

using fl = double;
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
        P = P - center;
        auto ang = atan2l(P.y, P.x);
        return (ang < 0 ? ang + 2 * PI : ang);
    }
    bool contains_inside(Circle C) {
        return (center - C.center).abs() + C.rad < rad;
    }
    vector<Point> intersection(Segment<Point> L) {
        vector<Point> res;
        Point ab = (L.p2 - L.p1).normalize(), ac = center - L.p1, proj = L.p1 + ab * ac.inner(ab);
        auto dist_to_mid = (proj - center).abs();
        if(rad < dist_to_mid) return res;
        auto dev = sqrt(rad * rad - dist_to_mid * dist_to_mid);
        if(dev <= eps) { // or <= eps
            res.push_back(proj);
        } else {
            res.push_back(proj + ab * dev); res.push_back(proj - ab * dev);
        }
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
        if(dev <= eps) { // or <= eps
            res.push_back(mid);
        } else {
            res.push_back(mid + ortho * dev); res.push_back(mid - ortho * dev);
            if((res[0] - center).turn(C.center - res[0]) != Point::CCW) swap(res[0], res[1]);
        }
        return res;
    }
    template <class output_stream>
    friend output_stream &operator<<(output_stream & out, Circle C) {
        return out << "[" << C.center << ", " << C.rad << "]";
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<tuple<int, int, Circle<fl, Point<fl>>>> circles;
    vector<fl> vol(n), dv(n, 0); dv[0] = 100;
    vector<vector<fl>> share(n, vector<fl>(n, 0));
    vector<bool> dead(n, false);
    for(int i = 0; i < n; i++) {
        int x, y, z, r, tv; cin >> x >> y >> z >> r >> tv;
        circles.emplace_back(z, tv, Circle<fl, Point<fl>>(Point<fl>(x, y), r));
    }
    sort(circles.begin(), circles.end(), [](auto c1, auto c2) {
        return get<0>(c1) > get<0>(c2);
    });
    for(int i = 0; i < n; i++) vol[i] = get<1>(circles[i]);
    int ct = 0; fl res = 0;
    for(int i = 0; i < n; i++) {
        fl tm = 1e18; int fst = -1;
        fill(dv.begin() + 1, dv.end(), 0);
        for(int j = 0; j < n; j++) {
            for(int k = j + 1; k < n; k++) {
                dv[k] += dv[j] * share[j][k];
            }
        }
        for(int j = 0; j < n; j++) {
            if(dv[j] == 0 || dead[j]) continue;
            if(vol[j] / dv[j] < tm) {
                tm = vol[j] / dv[j], fst = j;
            }
        }
        if(fst == -1) continue;
        res += tm; dead[fst] = true; ++ct;
        for(int j = 0; j < n; j++) {
            vol[j] = max(fl(0), vol[j] - tm * dv[j]);
        }
        vector<pair<fl, fl>> angs(1, make_pair(0, 2 * PI));
        for(int j = fst + 1; j < n; j++) {
            auto [z1, v1, c1] = circles[fst]; auto [z2, v2, c2] = circles[j];
            if(z2 >= z1) continue;
            vector<pair<fl, fl>> cut;
            auto pts = c1.intersection(c2);
            if(c2.contains_inside(c1)) {
                cut.emplace_back(0, 2 * PI);
            } else if((int) pts.size() == 2) {
                fl ang1 = c1.arg(pts[0]), ang2 = c1.arg(pts[1]);
                if(ang1 < ang2 + eps) {
                    cut.emplace_back(ang1, ang2);
                } else {
                    cut.emplace_back(ang1, 2 * PI); cut.emplace_back(0, ang2);
                }
            }
            for(auto [l, r]: cut) {
                vector<pair<fl, fl>> new_vec;
                for(auto [a1, a2]: angs) {
                    fl overlap = max(fl(0), min(a2, r) - max(a1, l));
                    share[fst][j] += overlap / (2 * PI);
                    if(a1 < l) new_vec.emplace_back(a1, min(a2, l));
                    if(a2 > r) new_vec.emplace_back(max(r, a1), a2);
                }
                angs = new_vec;
            }
        }
    }
    if(ct == n) {
        cout << fixed << setprecision(2) << res << '\n';
    } else {
        cout << "Invalid\n";
    }
}