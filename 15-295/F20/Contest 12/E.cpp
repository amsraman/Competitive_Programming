#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

struct Point {
    int x_val, y_val;
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
    ll inner(const Point & P) {
        return 1LL * x_val * P.x_val + 1LL * y_val * P.y_val;
    }
    long double norm() {
        return sqrt((long double) inner(*this));
    }
    ll cross(const Point & P) {
        return 1LL * x_val * P.y_val - 1LL * y_val * P.x_val;
    }
    int turn(const Point & P) {
        if(1LL * x_val * P.y_val > 1LL * y_val * P.x_val) {
            return 1;
        } else if(1LL * x_val * P.y_val == 1LL * y_val * P.x_val) {
            return 0;
        }
        return -1;
    }
};

vector<Point> ConvexHull(vector<Point> points) {
    if(points.size() <= 1) {
        return points;
    }
    sort(points.begin(), points.end());
    vector<Point> hull(points.size() + 1);
    int s = 0, t = 0;
    for(int it = 2; it--; s = --t, reverse(points.begin(), points.end())) {
        for(Point p: points) {
            while(t >= s + 2 && (hull[t - 1] - hull[t - 2]).cross(p - hull[t - 2]) <= 0) {
                t--;
            }
            hull[t++] = p;
        }
    }
    return {hull.begin(), hull.begin() + t - (t == 2 && hull[0] == hull[1])};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<Point> points(k);
    ll area = 0, ans = 0;
    for(int i = 0; i < k; i++) {
        cin >> points[i].x_val >> points[i].y_val;
    }
    vector<Point> inner_hull = ConvexHull(points);
    points.resize(n);
    for(int i = 0; i < n - k; i++) {
        cin >> points[i + k].x_val >> points[i + k].y_val;
    }
    vector<Point> outer_hull = ConvexHull(points);
    int isz = inner_hull.size(), osz = outer_hull.size(), p1 = 0, p2 = 0;
    vector<ll> ps(isz + 1, 0);
    auto is_endpoint = [&](int i_ind, int o_ind, bool beg) {
        int pv_ind = (i_ind + isz - 1) % isz, nx_ind = (i_ind + 1) % isz;
        if(inner_hull[i_ind] == outer_hull[o_ind]) {
            return true;
        } else if(inner_hull[pv_ind] == outer_hull[o_ind] || inner_hull[nx_ind] == outer_hull[o_ind]) {
            return false;
        }
        Point v1 = inner_hull[i_ind] - inner_hull[nx_ind];
        Point v2 = inner_hull[pv_ind] - inner_hull[i_ind];
        Point v3 = inner_hull[i_ind] - outer_hull[o_ind];
        if(beg) {
            return v3.turn(v2) == -1 && v3.turn(v1) >= 0;
        }
        return v3.turn(v1) == -1 && v3.turn(v2) >= 0;
    };
    for(int i = 0; i < isz; i++) {
        if(is_endpoint(i, 0, 1)) {
            p1 = i;
        }
        if(is_endpoint(i, 0, 0)) {
            p2 = i;
        }
        area += ps[i + 1] = inner_hull[i].cross(inner_hull[(i + 1) % isz]);
        ps[i + 1] += ps[i];
    }
    auto get_range_sum = [&](int x, int y) {
        if(x == y) {
            return 0LL;
        }
        y = (y + isz - 1) % isz;
        if(y < x) {
            return ps[y + 1] + ps[isz] - ps[x];
        }
        return ps[y + 1] - ps[x];
    };
    for(int i = 0; i < osz; i++) {
        while(!is_endpoint(p1, i, 1)) {
            p1 = (p1 + 1) % isz;
        }
        while(!is_endpoint(p2, i, 0)) {
            p2 = (p2 + 1) % isz;
        }
        ans = max(ans, area - get_range_sum(p1, p2) + inner_hull[p1].cross(outer_hull[i]) + outer_hull[i].cross(inner_hull[p2]));
    }
    cout << fixed << setprecision(1) << (long double) ans / 2.0 << '\n';
}