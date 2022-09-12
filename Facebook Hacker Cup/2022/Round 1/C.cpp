#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 0xfffffffffffffff;

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
    ifstream cin("lemonade_life_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, k, d;
        cin >> n >> k >> d;
        vector<Point> points(n), hull;
        for(int i = 0; i < n; i++) {
            cin >> points[i].x_val >> points[i].y_val;
        }
        hull = ConvexHull(points), n = hull.size();
        sort(hull.begin(), hull.end());
        auto dist = [&](int x, int y) {
            int dx = hull[x].x_val - hull[y].x_val, dy = hull[x].y_val - hull[y].y_val;
            return 1LL * dx * dx + 1LL * dy * dy;
        };
        vector<ll> dp(n, INF);
        vector<bool> vis(n, false);
        dp[0] = 0;
        for(int i = 0, cur = 0; i < n; i++) {
            vis[cur] = true;
            int nxt = -1;
            for(int j = 0; j < n; j++) {
                if(!vis[j]) {
                    if(dist(cur, j) <= 1LL * d * d) {
                        dp[j] = min(dp[j], dp[cur] + max(1LL * k, dist(cur, j)));
                    }
                    if(nxt == -1 || dp[j] < dp[nxt]) {
                        nxt = j;
                    }
                }
            }
            cur = nxt;
        }
        cout << "Case #" << _ << ": " << (dp[n - 1] == INF ? -1 : dp[n - 1]) << endl;
    }
}