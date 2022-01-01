#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 0xfffffffffffffff;

int n, a[200002], sz;
map<pair<int, int>, int> ind;
vector<ll> dp;
vector<array<ll, 5>> edges;
vector<vector<pair<int, ll>>> g;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i + 1];
    }
    stack<pair<int, int>> s1;
    stack<array<int, 3>> s2;
    // Creating Left Pointers
    for(int i = 1; i <= n; i++) {
        if(a[i] > 1) {
            s1.push({i, a[i] - 1});
        } else if(a[i] == 1 || s1.empty()) {
            continue;
        } else {
            pair<int, int> tp = s1.top();
            s1.pop();
            if(tp.s != 1) {
                s1.push({tp.f, tp.s - 1});
            }
            ind[{tp.f, tp.s - 1}] = ind[{i + 1, 0}] = 1;
            edges.push_back({tp.f, tp.s - 1, i + 1, 0, i - tp.f});
        }
    }
    // Creating Right Pointers
    for(int i = n + 1; i >= 0; i--) {
        if(a[i] > 1) {
            s2.push({i, a[i] - 1, 0});
        } else if(a[i] == 1 || s2.empty()) {
            continue;
        } else {
            array<int, 3> tp = s2.top();
            s2.pop();
            if(tp[2] != tp[1] - 1) {
                s2.push({tp[0], tp[1], tp[2] + 1});
            }
            ind[{i, 0}] = ind[{tp[0], tp[2] + 1}] = 1;
            edges.push_back({i, 0, tp[0], tp[2] + 1, tp[0] - i});
        }
    }
    ll tot1 = 0, tot2 = 0;
    // Slide complete to the left
    for(int i = 1; i <= n; i++) {
        tot1 += a[i];
        if(a[i] > 0 && tot1 > i) {
            ind[{0, 0}] = ind[{i, a[i] - 1}] = 1;
            edges.push_back({0, 0, i, a[i] - 1, tot1 - 1});
        }
    }
    // Slide complete to the right
    for(int i = n + 1; i > 0; i--) {
        tot2 += a[i];
        if(a[i] > 0 && tot2 > n - i + 1) {
            ind[{i, 0}] = ind[{n + 1, 0}] = 1;
            edges.push_back({i, 0, n + 1, 0, tot2 - 1});
        }
    }
    for(int i = 0; i <= n; i++) {
        if(a[i] <= 1) {
            ind[{i, 0}] = ind[{i + 1, 0}] = 1;
            edges.push_back({i, 0, i + 1, 0, 0});
        } else {
            ind[{i, a[i] - 1}] = ind[{i + 1, 0}] = 1;
            edges.push_back({i, a[i] - 1, i + 1, 0, 0});
        }
    }
    for(auto it: ind) {
        ind[it.f] = sz++;
    }
    g.resize(sz), dp.resize(sz, INF);
    // Add "Make-Room-Then-Drop" operation bounds
    pair<int, int> pv = {-1, 0};
    for(auto it: ind) {
        if(pv.f == it.f.f) {
            edges.push_back({pv.f, pv.s, it.f.f, it.f.s, 2 * (it.f.s - pv.s)});
        }
        pv = it.f;
    }
    for(array<ll, 5> e: edges) {
        g[ind[{e[0], e[1]}]].push_back({ind[{e[2], e[3]}], e[4]});
    }
    priority_queue<pair<ll, int>> q;
    dp[0] = 0, q.push({0, 0});
    while(!q.empty()) {
        pair<ll, int> tp = q.top();
        q.pop();
        if(-tp.f > dp[tp.s]) {
            continue;
        }
        for(pair<int, ll> e: g[tp.s]) {
            if(dp[tp.s] + e.s < dp[e.f]) {
                dp[e.f] = dp[tp.s] + e.s;
                q.push({-dp[e.f], e.f});
            }
        }
    }
    cout << dp[sz - 1] << '\n';
}