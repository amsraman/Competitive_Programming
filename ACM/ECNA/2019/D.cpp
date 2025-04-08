#include <bits/stdc++.h>

using namespace std;

using fl = double;
const fl eps = 1e-7;

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

int main() {
    int w, h, n, m, r, s; fl l; cin >> w >> h >> n >> m >> l >> r >> s;
    Point<fl> init_spot(l, 0), init_dir(r, s);
    init_dir = init_dir / init_dir.abs();
    vector<vector<Point<fl>>> polygons(m);
    vector<int> val(m), lbl(4, -1);
    vector<bool> dead(m, false);
    vector<multiset<fl>> hit_times(m);
    vector<Segment<Point<fl>>> lines;
    Point<fl> c1(0, 0), c2(w, 0), c3(0, h), c4(w, h);
    lines.emplace_back(c1, c2);
    lines.emplace_back(c1, c3);
    lines.emplace_back(c2, c4);
    lines.emplace_back(c3, c4);
    for(int i = 0; i < m; i++) {
        int p; cin >> p; polygons[i].resize(p);
        for(int j = 0; j < p; j++) {
            cin >> polygons[i][j].x >> polygons[i][j].y;
        }
        for(int j = 0; j < p; j++) {
            lines.emplace_back(polygons[i][j], polygons[i][(j + 1) % p]);
            lbl.push_back(i);
        }
        cin >> val[i];
    }
    priority_queue<tuple<fl, int, int, int>, vector<tuple<fl, int, int, int>>, greater<tuple<fl, int, int, int>>> q;
    vector<fl> lst_tm(n, 0); vector<Point<fl>> pl(n, init_spot), dr(n, init_dir);
    auto fst_intersection = [&](int x, int f1, int f2) -> pair<fl, int> {
        Segment<Point<fl>> ray(pl[x], pl[x] + dr[x] * 2000);
        fl best_time = 1e18; int ln = -1;
        for(int i = 0; i < (int) lines.size(); i++) {
            if(i == f1 || i == f2 || (lbl[i] >= 0 && dead[lbl[i]])) continue;
            auto res = lines[i].intersection(ray);
            if(res) {
                fl time_to_hit = (res.value() - pl[x]).abs();
                if(time_to_hit < best_time) {
                    best_time = time_to_hit;
                    ln = i;
                }
            }
        }
        assert(ln != -1);
        return make_pair(best_time, ln);
    };
    for(int i = 0; i < n; i++) {
        auto [tm, ln] = fst_intersection(lst_tm[i] = i, 0, -1);
        q.push({i + tm, i, ln, 0});
        if(lbl[ln] >= 0) {
            hit_times[lbl[ln]].insert(i + tm);
        }
    }
    int ct = 0;
    while(!q.empty()) {
        auto [tm, i, to, from] = q.top(); q.pop();
        if(to == 0) continue;
        bool reflect = lbl[to] == -1;
        if(lbl[to] >= 0) {
            int obj = lbl[to]; reflect = true;
            while((int) hit_times[obj].size() > val[obj]) {
                hit_times[obj].erase(prev(hit_times[obj].end()));
            }
            if(dead[obj]) {
                reflect = false;
            } else {
                if(hit_times[obj].size() == val[obj]) {
                    auto death_time = *prev(hit_times[obj].end());
                    if(tm >= death_time - eps) {
                        dead[obj] = true;
                        reflect = false;
                    }
                }
            }
        }
        if(reflect) { // reflect
            lst_tm[i] = tm;
            Segment<Point<fl>> ray(pl[i], pl[i] + dr[i] * 2000);
            auto pt = ray.intersection(lines[to]);
            assert(pt.has_value());
            pl[i] = pt.value();
            Point<fl> seg_dir = lines[to].p2 - lines[to].p1;
            complex<fl> unit_dir(seg_dir.x, seg_dir.y), in(dr[i].x, dr[i].y);
            unit_dir /= abs(unit_dir);
            complex<fl> out = unit_dir * unit_dir / in;
            dr[i] = {out.real(), out.imag()};
            assert((dr[i].abs() - 1) <= eps);      
            from = to, to = -1;
        }
        // recompute
        auto [new_tm, hit_ind] = fst_intersection(i, to, from);
        q.push({lst_tm[i] + new_tm, i, hit_ind, from});
        if(lbl[hit_ind] >= 0) {
            hit_times[lbl[hit_ind]].insert(lst_tm[i] + new_tm);
        }
    }
    for(int i = 0; i < m; i++) {
        cout << max(0, val[i] - (int) hit_times[i].size()) << " ";
    }
    cout << '\n';
}