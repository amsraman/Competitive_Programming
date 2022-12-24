#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int main() {
    int n; cin >> n;
    vector<pair<int, int>> points(n);
    for(int i = 0; i < n; i++) {
        cin >> points[i].f >> points[i].s;
    }
    auto choose2 = [](ll x) {
        return (1LL * x * (x - 1)) / 2;
    };
    auto radial_sort = [](vector<pair<pair<int, int>, int>> & vec) { // pain
        auto piv = partition(vec.begin(), vec.end(), [](pair<pair<int, int>, int> x) {
            return x.f >= make_pair(0, 0);
        });
        auto cmp = [](pair<pair<int, int>, int> p1, pair<pair<int, int>, int> p2) {
            return 1LL * p1.f.f * p2.f.s > 1LL * p1.f.s * p2.f.f;
        };
        sort(vec.begin(), piv, cmp); sort(piv, vec.end(), cmp);
    };
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        int above = 0;
        vector<pair<pair<int, int>, int>> ev;
        for(int j = 0; j < n; j++) {
            if(j != i) {
                pair<int, int> diff = {points[j].f - points[i].f, points[j].s - points[i].s};
                ev.push_back({{diff.f, diff.s}, -1});
                ev.push_back({{-diff.f, -diff.s}, 1});
                above += diff >= make_pair(0, 0);
            }
        }
        radial_sort(ev);
        for(auto [_, x]: ev) {
            if(x < 0) {
                above--;
                ans += 1LL * choose2(above) * choose2(n - above - 2);
            } else {
                above++;
            }
        }
    }
    cout << ans / 2 << endl;
}