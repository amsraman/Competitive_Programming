#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <typename T>
struct Point {
    T x_val, y_val;
    bool operator==(const Point &P) const {
        return (x_val == P.x_val && y_val == P.y_val);
    }
    bool operator<(const Point &P) const {
        return (x_val < P.x_val || x_val == P.x_val && y_val < P.y_val);
    }
    Point operator+(Point &P) {
        return {x_val + P.x_val, y_val + P.y_val};
    }
    Point operator-(Point &P) {
        return {x_val - P.x_val, y_val - P.y_val};
    }
    double norm() {
        return sqrt(x_val * x_val + y_val * y_val);
    }
    T inner(const Point &P) {
        return x_val * P.x_val + y_val * P.y_val;
    }
    T cross(const Point &P) {
        return x_val * P.y_val - y_val * P.x_val;
    }
    int turn(const Point &P) {
        if(abs(x_val * P.y_val - y_val * P.x_val) == 0) {
            return 0;
        } else if(x_val * P.y_val > y_val * P.x_val) {
            return 1;
        }
        return -1;
    }
};

int t;
Point<ll> t1, t2, t3, p;

void solve() {
    if((t1 - p).turn(t3 - p) == 0) {
        swap(t2, t3);
    } else if((t2 - p).turn(t3 - p) == 0) {
        swap(t1, t3);
    } else if((t1 - p).turn(t2 - p) != 0) {
        cout << -1 << '\n';
        return;
    }
    int dx1 = abs(p.x_val - t1.x_val), dx2 = abs(p.x_val - t2.x_val), dx3 = abs(t1.x_val - t2.x_val);
    if(t1.x_val == t2.x_val) {
        dx1 = abs(p.y_val - t1.y_val), dx2 = abs(p.y_val - t2.y_val), dx3 = abs(t1.y_val - t2.y_val);
    }
    if(dx1 + dx2 > dx3) {
        cout << -1 << '\n';
        return;
    }
    if(dx2 > dx1) {
        swap(t1, t2);
        swap(dx1, dx2);
    }
    int dx = t3.x_val - t1.x_val, dy = t3.y_val - t1.y_val;
    cout << fixed << setprecision(9);
    cout << (long double) t1.x_val + (long double) dx * (dx1 + dx2) / (2 * dx1) << " ";
    cout << (long double) t1.y_val + (long double) dy * (dx1 + dx2) / (2 * dx1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> t1.x_val >> t1.y_val >> t2.x_val >> t2.y_val >> t3.x_val >> t3.y_val >> p.x_val >> p.y_val;
        solve();
    }
}