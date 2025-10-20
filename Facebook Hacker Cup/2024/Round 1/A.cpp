#include <bits/stdc++.h>

using namespace std;

using fl = long double;

int main() {
    ifstream cin("subsonic_subway_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<pair<int, int>> rng;
        for(int i = 0, a, b; i < n; i++) {
            cin >> a >> b; rng.emplace_back(a, b);
        }
        fl min_speed = 0;
        for(int i = 0; i < n; i++) {
            auto [a, b] = rng[i];
            min_speed = max(min_speed, (fl) (i + 1) / b);
        }
        bool can = true;
        for(int i = 0; i < n; i++) {
            auto [a, b] = rng[i];
            if(min_speed * a > (i + 1)) can = false;
        }
        if(!can) min_speed = -1;
        cout << "Case #" << _ << ": " << fixed << setprecision(6) << min_speed << '\n';
    }
}
// distance = rate * time
// (i + 1) / rate \in [a, b]