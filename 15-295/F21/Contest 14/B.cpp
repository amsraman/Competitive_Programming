#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

ll n, x[2], y[2], ans;
pair<ll, ll> points[100000];

ll dist(int ind, int c) {
    return ((points[ind].f - x[c]) * (points[ind].f - x[c]) + (points[ind].s - y[c]) * (points[ind].s - y[c]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> x[0] >> y[0] >> x[1] >> y[1] >> n;
    for(int i = 0; i < n; i++) {
        cin >> points[i].f >> points[i].s;
    }
    vector<pair<ll, int>> circ1;
    set<pair<ll, int>> circ2;
    for(int i = 0; i < n; i++) {
        circ1.push_back({dist(i, 0), i});
        circ2.insert({dist(i, 1), i});
    }
    sort(circ1.begin(), circ1.end());
    ans = (--circ2.end())->f;
    for(int i = 0; i < n; i++) {
        circ2.erase(circ2.find({dist(circ1[i].s, 1), circ1[i].s}));
        ll rad2 = (circ2.empty() ? 0 : (--circ2.end())->f);
        ans = min(ans, circ1[i].f + rad2);
    }
    cout << ans << endl;
}