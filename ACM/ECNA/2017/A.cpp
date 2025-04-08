#include <bits/stdc++.h>
typedef long double ld;

using namespace std;

const ld eps = 1e-9, PI = 3.141592653589793238462643383297502884197;

template <typename T>
struct Point {
    T x, y;
    enum orientation {CW, CCW, STRAIGHT};
    Point operator+(const Point & P) {return {x + P.x, y + P.y};}
    Point operator-(const Point & P) {return {x - P.x, y - P.y};}
    Point operator*(T c) {return {x * c, y * c};}
    bool operator<(const Point & P) const {return tie(x, y) < tie(P.x, P.y);}
    bool operator==(const Point & P) const {return tie(x, y) == tie(P.x, P.y);} 
    T inner(const Point & P) const {return x * P.x + y * P.y;}
    T norm() {return inner(*this);}
    long double abs() {return sqrt(inner(*this));}
    T cross(const Point & P) {return x * P.y - y * P.x;}
    orientation turn(const Point & P) const {
        if(x * P.y > y * P.x + eps) {
            return CCW;
        } else if(x * P.y > y * P.x - eps) {
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
};

template <class Point>
struct Segment {
    Point p1, p2;
    bool intersects(Segment & S) {
        Point p11 = p1, p12 = p2, p21 = S.p1, p22 = S.p2;
        if((p21 - p11).turn(p12 - p21) == Point::STRAIGHT && (p11 - p21).turn(p22 - p11) == Point::STRAIGHT) {
            bool x_int = max(p11.x, p12.x) >= min(p21.x, p22.x) - eps && max(p21.x, p22.x) >= min(p11.x, p12.x) - eps;
            bool y_int = max(p11.y, p12.y) >= min(p21.y, p22.y) - eps && max(p21.y, p22.y) >= min(p11.y, p12.y) - eps;
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
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<vector<Point<ld>>> polygons(n);
    vector<ld> xs;
    ld paint = 0, cover = 0, one_degree = PI / 180;
    for(int i = 0; i < n; i++) {
        int m; cin >> m; polygons[i].resize(m);
        for(int j = 0; j < m; j++) {
            int x, y; cin >> x >> y;
            polygons[i][j] = {cosl(one_degree) * x - sinl(one_degree) * y, sinl(one_degree) * x + cosl(one_degree) * y};
            xs.push_back(polygons[i][j].x);
        }
        ld area = 0;
        for(int j = 0; j < m; j++) {
            area += polygons[i][j].cross(polygons[i][(j + 1) % m]);
        }
        if(area < 0) reverse(polygons[i].begin(), polygons[i].end());
        paint += abs(area) / 2.0;
    }
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int m1 = (int) polygons[i].size(), m2 = (int) polygons[j].size();
            for(int p1 = 0; p1 < m1; p1++) {
                Segment<Point<ld>> s1 = {polygons[i][p1], polygons[i][(p1 + 1) % m1]};
                for(int p2 = 0; p2 < m2; p2++) {
                    Segment<Point<ld>> s2 = {polygons[j][p2], polygons[j][(p2 + 1) % m2]};
                    auto touch = s1.intersection(s2);
                    if(touch) {
                        xs.push_back(touch.value().x);
                    }
                }
            }
        }
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    auto slice = [&](ld x) {
        ld len = 0;
        vector<pair<ld, ld>> segs;
        Segment<Point<ld>> big_line = {{x, -2002}, {x, 2002}};
        for(int i = 0; i < n; i++) {
            vector<pair<ld, bool>> ys;
            int sz = (int) polygons[i].size();
            for(int j = 0; j < sz; j++) {
                Segment<Point<ld>> side = {polygons[i][j], polygons[i][(j + 1) % sz]};
                auto touch = side.intersection(big_line);
                if(touch) {
                    ys.push_back(make_pair(touch.value().y, side.p1.x < side.p2.x));
                }
            }
            sort(ys.begin(), ys.end());
            ys.erase(unique(ys.begin(), ys.end()), ys.end());
            assert(ys.size() % 2 == 0);
            for(int j = 0; j + 1 < (int) ys.size(); j += 2) {
                segs.emplace_back(ys[j].first, ys[j + 1].first);
            }
        }
        sort(segs.begin(), segs.end());
        pair<ld, ld> cur = {-1e18, -1e18};
        for(auto [l, r]: segs) {
            if(l > cur.second + eps) {
                len += cur.second - cur.first;
                cur = {l, r};
            } else {
                cur.second = max(cur.second, r);
            }
        }
        return len + cur.second - cur.first;
    };
    for(int i = 0; i < (int) xs.size() - 1; i++) {
        cover += (slice(xs[i]) + slice(xs[i + 1])) * (xs[i + 1] - xs[i]) / 2;
    }
    cout << fixed << setprecision(6) << paint << " " << cover << '\n';
}