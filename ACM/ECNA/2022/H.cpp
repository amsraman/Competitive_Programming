#include <bits/stdc++.h>

using namespace std;

using fl = long double;

const fl eps = 1e-9, lim = 1e9, inf = 1e18;

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
        } else if(x * P.y + eps < y * P.x) {
            return CW;
        }
        return STRAIGHT;
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
    bool intersects(const Segment S) {
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
    optional<Point> intersection(Segment S) {
        if(!intersects(S)) {
            return nullopt;
        }
        if(p1 == p2) return p1;
        if(S.p1 == S.p2) return S.p1;
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

using pt = Point<fl>;
using seg = Segment<pt>;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<pt> pts;
    for(int i = 0; i <= n; i++) {
        int x, y; cin >> x >> y; pts.emplace_back(x, y);
    }
    fl c, r, v; pt s, d; cin >> c >> s.x >> s.y >> r >> d.x >> d.y >> v;
    d = d / d.abs();
    seg big(s, s + d * lim);
    auto time_to_touch = [&](seg cur_seg) -> fl {
        auto inter = cur_seg.intersection(big);
        pt closest_point = (big.dist(cur_seg.p1) <= big.dist(cur_seg.p2) ? cur_seg.p1 : cur_seg.p2);
        if(inter.has_value()) closest_point = inter.value();
        if(big.dist(closest_point) > r) return inf;
        if(cur_seg.dist(s) <= r) return 0;
        fl lb = 0, ub = d.inner(closest_point - s);
        assert(ub >= 0);
        for(int it = 0; it < 50; it++) {
            fl mid = (lb + ub) / 2;
            pt cur = s + d * mid;
            if(cur_seg.dist(cur) <= r) {
                ub = mid;
            } else {
                lb = mid;
            }
        }
        return ub;
    };
    // If we're currently outside the x range, bring it in
    if(s.x < pts[0].x - r || s.x > pts[n].x + r) {
        if(abs(d.x) < eps) {
            cout << "-1\n";
            return 0;
        }
        fl tm = min(abs(pts[0].x - r - s.x), abs(pts[n].x + r - s.x)) / d.x;
        s = s + d * tm;
    }
    fl ans = inf;
    int ptr = 1;
    while(pts[ptr].x < c) ++ptr;
    // Go forwards
    pt me = (pts[ptr - 1] * (pts[ptr].x - c) + pts[ptr] * (c - pts[ptr - 1].x)) / (pts[ptr].x - pts[ptr - 1].x), lst = pts[ptr];
    ans = min(ans, time_to_touch(seg(me, pts[ptr])));
    for(int i = ptr + 1; i <= n; i++) {
        auto cur_turn = (lst - me).turn(pts[i] - lst);
        if(cur_turn != pt::CW) {
            pt dir = lst - me;
            if(cur_turn == pt::CCW) {
                dir = dir / dir.abs();
                seg ray(lst, lst + dir * lim);
                pt inter = ray.intersection(seg(pts[i - 1], pts[i])).value();
                ans = min({ans, time_to_touch(seg(me, inter)), time_to_touch(seg(inter, pts[i]))});
            }
            lst = pts[i];
        }
    }
    if((lst - me).abs() > eps) { // the top peak
        pt dir = lst - me; dir = dir / dir.abs();
        fl tms = abs(dir.x) < eps ? lim : ((pts[n].x - me.x) / dir.x);
        ans = min(ans, time_to_touch(seg(me, me + dir * tms)));
    }
    // Go backwards
    lst = pts[ptr - 1];
    ans = min(ans, time_to_touch(seg(pts[ptr - 1], me)));
    for(int i = ptr - 2; i >= 0; i--) {
        auto cur_turn = (lst - me).turn(pts[i] - lst);
        if(cur_turn != pt::CCW) {
            pt dir = lst - me;
            if(cur_turn == pt::CW) {
                dir = dir / dir.abs();
                seg ray(lst, lst + dir * lim);
                pt inter = ray.intersection(seg(pts[i + 1], pts[i])).value();
                ans = min({ans, time_to_touch(seg(inter, me)), time_to_touch(seg(pts[i], inter))});
            }
            lst = pts[i];
        }
    }
    if((lst - me).abs() > eps) { // the top peak
        pt dir = lst - me; dir = dir / dir.abs();
        fl tms = abs(dir.x) < eps ? lim : ((me.x - pts[0].x) / abs(dir.x));
        ans = min(ans, time_to_touch(seg(me, me + dir * tms)));
    }
    // maybe we are just immediately done?
    seg direct(me, s); bool works = true;
    for(int i = 0; i < n; i++) {
        if(direct.intersects(seg(pts[i], pts[i + 1]))) {
            works = false;
            break;
        }
    }
    if(works) ans = 0;
    if(ans == inf) {
        cout << "-1\n";
    } else {
        cout << fixed << setprecision(9) << ans / v << '\n';
    }
}
/*
Claim:
- Our line of sight either touches a peak, or we first see a cloud as it hits the mountain.
*/