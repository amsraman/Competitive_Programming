#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <typename T>
struct frac {
    T num, den;
    frac(): num(0), den(1) {};
    frac(T c): num(c), den(1) {};
    frac(T n, T d): num(n), den(d) {
        T g = __gcd(num, den);
        num /= g, den /= g;
        if(den < 0) {
            num *= -1, den *= -1;
        }
    };
    bool operator==(T cons) {return (cons * this->den == this->num);}
    bool operator!=(T cons) {return (cons * this->den != this->num);}
    bool operator<(T cons) {return (this->num < cons * this->den);}
    bool operator>(T cons) {return (this->num > cons * this->den);}
    inline int frac_cmp(const frac & f) const {
        T g = __gcd(this->den, f.den), q1 = (this->num * (f.den / g)), q2 = (f.num * (this->den / g));
        return (q1 == q2 ? 1 : q1 < q2 ? 0 : 2);
    }
    bool operator==(const frac & f) const {return (frac_cmp(f) == 1);}
    bool operator!=(const frac & f) const {return (frac_cmp(f) != 1);}
    bool operator<(const frac & f) const {return (frac_cmp(f) == 0);}
    bool operator>(const frac & f) const {return (frac_cmp(f) == 2);}
    bool operator<=(const frac & f) const {return (frac_cmp(f) != 2);}
    bool operator>=(const frac & f) const {return (frac_cmp(f) != 0);}
    frac operator+(const frac & f) const {
        T g = __gcd(this->den, f.den), lcm = this->den / g * f.den;
        return frac(this->num * (f.den / g) + f.num * (this->den / g), lcm);
    }
    frac operator-(const frac & f) const {
        T g = __gcd(this->den, f.den), lcm = this->den / g * f.den;
        return frac(this->num * (f.den / g) - f.num * (this->den / g), lcm);
    }
    frac operator*(T coef) {
        T g = __gcd(coef, this->den);
        return frac(this->num * (coef / g), this->den / g);
    }
    frac operator*(const frac & f) const {
        T g1 = __gcd(this->num, f.den), g2 = __gcd(this->den, f.num);
        return frac((this->num / g1) * (f.num / g2), (this->den / g2) * (f.den / g1));
    }
    frac operator/(T coef) {
        T g = __gcd(coef, this->num);
        return frac(this->num / g, this->den * (coef / g));
    }
    frac operator/(const frac & f) const {
        T g1 = __gcd(this->num, f.num), g2 = __gcd(this->den, f.den);
        return frac((this->num / g1) * (f.den / g2), (this->den / g2) * (f.num / g1));
    }
    void operator+=(const frac & f) {*this = *this + f;}
    void operator-=(const frac & f) {*this = *this - f;}
    void operator*=(T coef) {*this = *this * coef;}
    void operator*=(const frac & f) {*this = *this * f;}
    void operator/=(T coef) {*this = *this / coef;}
    void operator/=(const frac & f) {*this = *this / f;}
    friend T floor(const frac & f) {return f.num >= 0 ? f.num / f.den : -((-f.num + f.den - 1) / f.den);}
    template <class output_stream>
    friend output_stream &operator<<(output_stream & out, const frac & f) {
        return out << f.num << "/" << f.den;
    }
};

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
    bool operator>(const Point & P) const {return tie(x, y) > tie(P.x, P.y);}
    bool operator==(const Point & P) const {return tie(x, y) == tie(P.x, P.y);} 
    T inner(const Point & P) const {return x * P.x + y * P.y;}
    T norm() {return inner(*this);}
    long double abs() {return sqrt(inner(*this));}
    Point normalize() {return (*this) / abs();}
    T cross(const Point & P) {return x * P.y - y * P.x;}
    orientation turn(const Point & P) const {
        if(x * P.y > y * P.x) {
            return CCW;
        } else if(x * P.y < y * P.x) {
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
struct Line {
    Point p1, p2;
	Line() {};
	Line(Point p1, Point p2): p1(p1), p2(p2) {};
    template <typename T>
    optional<Point> point_at(T x) {
        if(p1.x == p2.x) {
            return nullopt;
        }
        return p1 + (p2 - p1) / (p2.x - p1.x) * (x - p1.x);
    }
    optional<Point> intersection(Line & L) {
        if((p1 - p2).turn(L.p1 - L.p2) == Point::STRAIGHT) {
            return nullopt;
        }
        auto t = (L.p1 - p1).cross(L.p2 - L.p1) / (p2 - p1).cross(L.p2 - L.p1);
        return p1 * (t * -1 + 1) + p2 * t;
    }
    template <class output_stream>
    friend output_stream &operator<<(output_stream & out, Line L) {
        return out << "[" << L.p1 << ", " << L.p2 << "]";
    }
};

using fl = frac<ll>;
using pt = Point<fl>;
using line = Line<pt>;

template <typename T>
T floor_sum(T n, T m, T a, T b) { // returns \sum_{i=0}^{n-1} floor((Ai+B)/m)
    if(a < 0) tie(a, b) = make_pair(-a, a * (n - 1) + b);
    T res = 0;
    while(n > 0) {
        res += n * (n - 1) / 2 * (a / m), a %= m;
        res += n * (b / m), b %= m;
        tie(n, m, a, b) = make_tuple((a * n + b) / m, a, m, (a * n + b) % m);
    }
    return res;
}

const ll big = 1.1e6;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<pt> pts;
    for(int i = 0, x, y; i < n; i++) {
        cin >> x >> y; pts.emplace_back(x, y);
    }
    ll ans = 0; bool inf = false;
    auto contains_integer = [&](fl a, fl b) {
        if(a > b) swap(a, b);
        return fl(floor(a) + 1) < b;
    };
    auto is_integral = [&](pt a) -> int {
        return (a.x.den == 1) && (a.y.den == 1);
    };
    auto on_line = [&](pt a, pt b) -> ll {
        if(a.x == b.x) return floor(b.y - a.y) + 1 - is_integral(a) - is_integral(b);
        pt dif = b - a; auto [x, y] = make_pair(abs(dif.x.num * dif.y.den), abs(dif.y.num * dif.x.den));
        ll g = __gcd(x, y); x /= g, y /= g;
        return floor((b - a).x / fl(x)) + 1 - is_integral(a) - is_integral(b);
    };
    auto under_line = [&](pt a, pt b) -> ll {
        if(a.x == b.x) return on_line(a, b) + is_integral(b);
        ll lb = 1 + floor(a.x), ub = floor(b.x);
        if(lb > ub) return 0;
        line l(a, b); tie(a, b) = make_pair(l.point_at((fl) lb).value(), l.point_at((fl) ub).value());
        if(lb == ub) return floor(a.y);
        fl slope = (b.y - a.y) / (b.x - a.x);
        ll g = __gcd(slope.den, a.y.den), m = slope.den / g * a.y.den;
        return floor_sum<ll>(ub - lb + 1, m, a.y.den / g * slope.num, slope.den / g * a.y.num);
    };
    auto solve_triangle = [&](pt a, pt b, pt c) -> ll {
        if(a > b) swap(a, b);
        if(a > c) swap(a, c);
        if(b > c) swap(b, c);
        a.y += fl(big); b.y += fl(big); c.y += fl(big);
        auto turn = (b - a).turn(c - b); ll res = 0;
        if(turn == pt::CW) { // middle is above
            res = under_line(a, b) + under_line(b, c) - under_line(a, c);
            res -= on_line(a, b) + on_line(b, c) + is_integral(b);
        } else { // middle is below
            res = under_line(a, c) - under_line(a, b) - under_line(b, c);
            res -= on_line(a, c);
        }
        assert(res >= 0);
        return res;
    };
    for(int i = 0; i < n; i++) {
        pt p1 = pts[(i + 1) % n], p2 = pts[(i + 2) % n];
        line l1(pts[i], p1), l2(p2, pts[(i + 3) % n]);
        auto opt = l1.intersection(l2);
        if(!opt) { // handle tunnels separately
            if(l1.p1.x == l1.p2.x) {
                if(contains_integer(l1.p1.x, l2.p1.x)) inf = true;
            } else {
                for(int j = 0; j < 2000; j++) {
                    if(contains_integer(l1.point_at(fl(j)).value().y, l2.point_at(fl(j)).value().y)) {
                        inf = true;
                        break;
                    }
                }
            }
            continue;
        }
        pt p3 = opt.value();
        if((p3 - p1).turn(p2 - p3) != pt::CCW) {
            inf = true;
            continue;
        }
        ans += solve_triangle(p1, p2, p3);
    }
    if(inf) {
        cout << "infinitely many\n";
    } else {
        cout << ans << '\n';
    }
}