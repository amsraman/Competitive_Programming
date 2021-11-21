#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, ans;
pair<int, int> points[1000];
map<pair<pair<int, int>, ll>, int> rect;

int main() {
    cin >> n;
    set<pair<int, int>> point_set;
    for(int i = 0; i < n; i++) {
        cin >> points[i].f >> points[i].s;
    }
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            pair<int, int> mp = {points[i].f + points[j].f, points[i].s + points[j].s};
            ll dist = (points[i].f - points[j].f) * (points[i].f - points[j].f) + (points[i].s - points[j].s) * (points[i].s - points[j].s);
            ans += rect[{mp, dist}];
            ++rect[{mp, dist}];
        }
    }
    cout << ans << endl;
}