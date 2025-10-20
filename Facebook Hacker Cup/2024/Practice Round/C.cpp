#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ifstream cin("fall_in_line_input.txt");
    ofstream cout("out.txt");
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    auto rand_int = [&](int x, int y) {
        return uniform_int_distribution<int>(x, y)(rng);
    };
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<pair<int, int>> pts;
        for(int i = 0, x, y; i < n; i++) {
            cin >> x >> y; pts.emplace_back(x, y);
        }
        map<tuple<int, int, ll>, int> ct; int mx = 0;
        for(int it = 0; it < 20; it++) {
            int ind = rand_int(0, n - 1);
            for(int i = 0; i < n; i++) {
                if(i == ind) continue;
                auto [px, py] = pts[i];
                auto [nx, ny] = pts[ind];
                int dx = nx - px, dy = py - ny;
                int g = __gcd(dx, dy);
                dx /= g, dy /= g;
                if(dx < 0) dx *= -1, dy *= -1;
                if(dx == 0 && dy < 0) dy *= -1;
                ll c = 1LL * dx * py + 1LL * dy * px;
                ++ct[make_tuple(dx, dy, c)];
            }
            for(auto it: ct) mx = max(mx, it.second + 1);
            ct.clear();
        }
        cout << "Case #" << _ << ": " << n - mx << endl;
    }
}