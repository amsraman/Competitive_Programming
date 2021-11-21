#include <bits/stdc++.h>
typedef long long ll;
#define int long long

using namespace std;

int t, k;
array<int, 4> coords[100000];

ll x_dist(int x) {
    ll ret = 0;
    for(int i = 0; i < k; i++) {
        if(x < coords[i][0] || x > coords[i][2]) {
            ret += min(abs(x - coords[i][0]), abs(x - coords[i][2]));
        }
    }
    return ret;
}

ll y_dist(int y) {
    ll ret = 0;
    for(int i = 0; i < k; i++) {
        if(y < coords[i][1] || y > coords[i][3]) {
            ret += min(abs(y - coords[i][1]), abs(y- coords[i][3]));
        }
    }
    return ret;
}

int find_x() {
    int lb = -2e9, ub = 2e9;
    while(lb < ub) {
        int mid = lb + (ub - lb) / 2;
        if(x_dist(mid) <= x_dist(mid + 1)) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    return ub;
}

int find_y() {
    int lb = -2e9, ub = 2e9;
    while(lb < ub) {
        int mid = lb + (ub - lb) / 2;
        if(y_dist(mid) <= y_dist(mid + 1)) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    return ub;
}

signed main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> k;
        for(int i = 0; i < k; i++) {
            cin >> coords[i][0] >> coords[i][1] >> coords[i][2] >> coords[i][3];
        }
        cout << "Case #" << _ << ": " << find_x() << " " << find_y() << endl;
    }
}