#include <bits/stdc++.h>

using namespace std;

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
    const T PI = 3.141592653589793238462643383279502884197, eps = 1e-9;
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
struct FlowNetwork {
    int n;
    T INF = numeric_limits<T>::max();
    vector<int> level, ptr;
    vector<vector<int>> graph;
    vector<vector<T>> init_capacity, edge_capacity;
    FlowNetwork(int n): n(n), level(n), ptr(n), graph(n), init_capacity(n), edge_capacity(n) {
        for(int i = 0; i < n; i++) {
            init_capacity[i].resize(n, 0);
            edge_capacity[i].resize(n, 0);
        }
    };
    void add_edge(int ind1, int ind2, T weight) {
        if(init_capacity[ind1][ind2] + init_capacity[ind2][ind1] == 0) {
            graph[ind1].push_back(ind2);
            graph[ind2].push_back(ind1);
        }
        init_capacity[ind1][ind2] += weight;
    }
    T dfs(int start, T cur_bottleneck, int end) {
        if(start == end) {
            return cur_bottleneck;
        }
        while(ptr[start] < (int) graph[start].size()) {
            int neighbor = graph[start][ptr[start]];
            while(level[neighbor] != level[start] + 1 || edge_capacity[start][neighbor] == 0) {
                ++ptr[start];
                if(ptr[start] == (int) graph[start].size()) {
                    break;
                }
                neighbor = graph[start][ptr[start]];
            }
            if(ptr[start] == (int) graph[start].size()) {
                break;
            }
            T final_bottleneck = dfs(neighbor, min(cur_bottleneck, edge_capacity[start][neighbor]), end);
            if(final_bottleneck > 0) {
                edge_capacity[start][neighbor] -= final_bottleneck;
                edge_capacity[neighbor][start] += final_bottleneck;
                return final_bottleneck;
            } else {
                ptr[start]++;
            }
        }
        return 0;
    }
    T dinic_flow(int source, int sink) {
        T flow = 0;
        bool path_exists = true;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                edge_capacity[i][j] = init_capacity[i][j];
            }
        }
        while(path_exists) {
            queue<int> q;
            fill(level.begin(), level.end(), 0);
            fill(ptr.begin(), ptr.end(), 0);
            q.push(source), level[source] = 1;
            while(!q.empty()) {
                int cur_node = q.front();
                q.pop();
                for(int next_node: graph[cur_node]) {
                    if(level[next_node] == 0 && edge_capacity[cur_node][next_node] != 0) {
                        level[next_node] = level[cur_node] + 1;
                        q.push(next_node);
                    }
                }
            }
            path_exists = (level[sink] > 0);
            if(!path_exists) {
                continue;
            }
            while(T extra = dfs(source, INF, sink)) {
                flow += extra;
            }
        }
        return flow;
    }
    vector<pair<int, int>> min_cut(int source, int sink) {
        dinic_flow(source, sink);
        vector<bool> reachable(n, false); reachable[source] = true;
        queue<int> q; q.push(source);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v: graph[u]) {
                if(edge_capacity[u][v] > 0 && !reachable[v]) { // unsaturated
                    q.push(v); reachable[v] = true;
                }
            }
        }
        vector<pair<int, int>> res;
        for(int i = 0; i < n; i++) {
            for(int j: graph[i]) {
                if(reachable[i] && !reachable[j] && edge_capacity[i][j] == 0) {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }
};

using fl = long double;
using pt = Point<fl>;
using seg = Segment<pt>;
using circle = Circle<fl, pt>;
using arc = tuple<circle, fl, fl>;

int main() {
    int n, a, g; cin >> n >> a >> g;
    for(int _ = 1; n > 0; _++) {
        vector<seg> segs; vector<arc> arcs;
        for(int i = 0; i < n; i++) {
            int m; cin >> m;
            vector<pt> pts(m); vector<pair<char, pt>> sides(m);
            for(int j = 0; j < m; j++) {
                cin >> pts[j].x >> pts[j].y >> sides[j].first;
                if(sides[j].first == 'c') {
                    cin >> sides[j].second.x >> sides[j].second.y;
                }
            }
            for(int j = 0; j < m; j++) {
                if(sides[j].first == 's') {
                    segs.emplace_back(pts[j], pts[(j + 1) % m]);
                } else { // compute circle
                    pt x1 = pts[j], d1(-sides[j].second.y, sides[j].second.x);
                    pt x2 = (pts[j] + pts[(j + 1) % m]) / 2, d2(pts[(j + 1) % m].y - pts[j].y, pts[j].x - pts[(j + 1) % m].x);
                    pt center = x1 + d1 * ((x2.cross(d2) - x1.cross(d2)) / d1.cross(d2));
                    auto rad = (pts[j] - center).abs();
                    circle circ(center, rad);
                    auto a1 = circ.arg(pts[j]), a2 = circ.arg(pts[(j + 1) % m]);
                    if((pts[(j + 1) % m] - pts[j]).turn(sides[j].second) == pt::CCW) swap(a1, a2);
                    arcs.emplace_back(circ, a1, a2);
                }
            }
        }
        vector<pt> arts(a), guards(g);
        FlowNetwork<int> fn(a + g + 2); int sum_levs = 0;
        for(int i = 0; i < a; i++) {
            int lev; cin >> arts[i].x >> arts[i].y >> lev; sum_levs += lev;
            fn.add_edge(i + g + 1, a + g + 1, lev);
        }
        for(int i = 0; i < g; i++) {
            int lev; cin >> guards[i].x >> guards[i].y >> lev;
            fn.add_edge(0, i + 1, lev);
        }
        for(int i = 0; i < g; i++) {
            for(int j = 0; j < a; j++) {
                seg conn(guards[i], arts[j]);
                bool bad = false;
                for(auto sg: segs) {
                    if(conn.intersects(sg)) {
                        bad = true;
                        break;
                    }
                }
                if(bad) continue;
                for(auto [circ, a1, a2]: arcs) {
                    auto pts = circ.intersection(conn);
                    for(auto ipt: pts) {
                        if(ipt < min(guards[i], arts[j])) continue;
                        if(max(guards[i], arts[j]) < ipt) continue;
                        auto ang = circ.arg(ipt);
                        if(a1 <= a2) {
                            if(a1 <= ang && ang <= a2) {
                                bad = true;
                                break;
                            }
                        } else {
                            if(ang <= a2 || a1 <= ang) {
                                bad = true;
                                break;
                            }
                        }
                    }
                }
                if(bad) continue;
                fn.add_edge(i + 1, j + g + 1, 1);
            }
        }
        bool pos = fn.dinic_flow(0, a + g + 1) == sum_levs;
        cout << "Case " << _ << ": " << (pos ? "Yes" : "No") << '\n';
        cin >> n >> a >> g;
    }
}