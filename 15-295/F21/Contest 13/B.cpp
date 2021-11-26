#include <bits/stdc++.h>

using namespace std;

int n, y[1000];
bool pos = false;

bool parallel(long long fx, long long fy, long long sx, long long sy) {
    return fx * sy == fy * sx;
}

bool try_slope(int x_dif, int y_dif) {
    int g = __gcd(x_dif, abs(y_dif));
    x_dif /= g, y_dif /= g;
    pair<int, int> p2 = {-1, -1};
    for(int i = 1; i < n; i++) {
        if(parallel(x_dif, y_dif, i, y[i] - y[0])) {
            continue;
        }
        if(p2.first == -1) {
            p2 = {i, y[i]};
        }
        if(!parallel(x_dif, y_dif, i - p2.first, y[i] - p2.second)) {
            return false;
        }
    }
    return (p2.first != -1);
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> y[i];
    }
    for(int i = 1; i < n; i++) {
        pos |= try_slope(i, y[i] - y[0]);
    }
    if(n > 2) {
        pos |= try_slope(1, y[2] - y[1]);
    }
    cout << (pos ? "Yes" : "No") << endl;
}