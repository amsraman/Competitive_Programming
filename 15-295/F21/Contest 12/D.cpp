#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int q;
ll n, px, py, qx, qy;

void flip_neg() {
    py *= -1, qy *= -1;
}

void flip_pos() {
    ll tpx = py, tpy = px, tqx = qy, tqy = qx;
    px = tpx, py = tpy, qx = tqx, qy = tqy;
}

ll floor_div(ll x, ll y) {
    return x / y;
}

ll get_x() {
    return floor_div(px * (qy - py) - py * (qx - px), qy - py);
}

ll get_y() {
    return floor_div(py * (qx - px) - px * (qy - py), qx - px);
}

bool is_on_line(ll x, ll y) {
    return (y - py) * (qx - px) == (x - px) * (qy - py);
}

int main() {
    cin >> n >> q;
    while(q--) {
        cin >> px >> py >> qx >> qy;
        if(qx < px) {
            swap(px, qx);
            swap(py, qy);
        }
        // First, check if it intersects the origin
        if(px * qy == py * qx) {
            cout << 2 * n << '\n';
            continue;
        }
        // Then, check for horizontal or vertical lines
        if(px == qx) {
            if(px < 0) {
                px = -px;
            }
            if(px > n) {
                cout << 0 << "\n";
            } else {
                cout << 2 * (n - px) + 1 << '\n';
            }
            continue;
        }
        if(py == qy) {
            if(py < 0) {
                py = -py;
            }
            if(py > n) {
                cout << 0 << '\n';
            } else {
                cout << 2 * (n - py) + 1 << '\n';
            }
            continue;
        }
        // If the slop is negative, flip across y = -x
        if((py - qy) * (px - qx) < 0) {
            flip_neg();
        }
        // If the y intercept is positive, flip across y = x
        if(qy * (qx - px) > qx * (qy - py)) {
            flip_pos();
        }
        ll mn = min(n, min(get_x(), -get_y()));
        cout << 2 * (n - min(n, mn)) + int(is_on_line(0, -mn) || is_on_line(mn, 0)) << '\n';
    }
}