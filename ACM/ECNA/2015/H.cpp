#include <bits/stdc++.h>

using namespace std;

using fl = double;
const fl eps = 1e-6, PI = 4 * atan(1);

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
    fl abs() {return sqrt(inner(*this));}
    Point normalize() {return (*this) / abs();}
    T cross(const Point & P) {return x * P.y - y * P.x;}
    orientation turn(const Point & P) const {
        if(x * P.y > y * P.x) {
            return CCW;
        } else if(x * P.y == y * P.x) {
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
    template <class output_stream>
    friend output_stream &operator<<(output_stream & out, Segment S) {
        return out << "[" << S.p1 << ", " << S.p2 << "]";
    }
};

int main() {
	int w, l; cin >> w >> l;
	Point<fl> p1, p2, p3, t1 = {w, l}, t2 = {0, l};
	int r, h; cin >> r >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> h;
	Point<fl> b1_targ = p3 - (t1 - p3).normalize() * 2 * r;
	Point<fl> cue_targ = p1 - (b1_targ - p1).normalize() * 2 * r;
	Point<fl> b2_targ = p2 - (t2 - p2).normalize() * 2 * r;
	auto reflect = [](Point<fl> v1, Point<fl> v2) { // reflect v1 across v2 (I guess sign doesn't matter)
		complex<fl> c1(v2.x, v2.y);
		complex<fl> c2(v1.x, v1.y);
		complex<fl> res = c1 * c1 / c2;
		return Point<fl>{res.real(), res.imag()};
	};
	Point<fl> down = reflect((b2_targ - cue_targ).normalize(), (b1_targ - p1).normalize()); // what happens if x coordinate is zero??????
	assert(down.y != 0);
	Point<fl> st = cue_targ - down * (cue_targ.y - h) / down.y;
	auto in_box = [&](Point<fl> p) {
		return p.x >= r && p.y >= r && p.x <= w - r && p.y <= l - r;
	};
	auto point_to_seg = [&](Point<fl> p1, Point<fl> s1, Point<fl> s2) {
		if(s2 < s1) swap(s1, s2);
		auto proj = s1 + (s2 - s1) * (p1 - s1).inner(s2 - s1) / (s2 - s1).abs() / (s2 - s1).abs();
		fl res = min((p1 - s1).abs(), (p1 - s2).abs());
		if(s1 < proj && proj < s2) {
			res = min(res, (p1 - proj).abs());
		}
		return res;
	};
	auto away = [&](Point<fl> s1, Point<fl> s2, vector<Point<fl>> bad) {
        Segment<Point<fl>> side = {s1, s2};
		for(auto pt: bad) {
			if(side.dist(pt) < 2 * r) {
				return false;
			}
		}
		return true;
	};
	bool ok = true;
	ok = ok && in_box(st);
	ok = ok && in_box(cue_targ);
	ok = ok && in_box(b1_targ);
	ok = ok && in_box(b2_targ);
	ok = ok && away(st, cue_targ, {p2, p3});
	ok = ok && away(cue_targ, b1_targ, {p2});
	ok = ok && away(b1_targ, t1, {p2});
	ok = ok && away(cue_targ, b2_targ, {p3});
	ok = ok && away(b2_targ, t2, {p1, p3});
	if(!ok) {
		cout << "impossible\n";
	} else {
		Point<fl> go = cue_targ - st;
		cout << fixed << setprecision(2) << st.x << " " << atan2(go.y, go.x) / PI * 180 << '\n';
	}
}