#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, n;
long long ans;
map<pair<int, int>, int> ang;

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0, x, y, u, v; i < n; i++) {
            cin >> x >> y >> u >> v;
            int dx = u - x, dy = v - y, g = __gcd(abs(dx), abs(dy));
            dx /= g, dy /= g;
            ++ang[{dx, dy}];
        }
        ans = 0;
        for(auto it: ang) {
            ans += (long long) it.s * ang[{-it.f.f, -it.f.s}];
        }
        cout << ans / 2 << endl;
        ang.clear();
    }
}