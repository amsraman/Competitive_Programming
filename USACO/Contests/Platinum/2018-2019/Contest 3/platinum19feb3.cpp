#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 0xfffffffffffffff;

int n, t, lev;
ll dp[200002];
pair<int, int> pts[200002];
vector<int> lis, levels[200002], seg[(1 << 19)];

void solve(int lo, int hi, int ind, int lb, int ub) {
    int best_ind = lo, mid = (lo + hi) >> 1, cur = seg[ind][mid];
    ll best = INF;
    for(int i = lb; i <= ub; i++) {
        int ind = levels[lev - 1][i];
        ll nxt = dp[ind] + 1LL * (pts[cur].f - pts[ind].f) * (pts[cur].s - pts[ind].s);
        if(nxt < best) {
            best = nxt, best_ind = i;
        }
    }
    dp[cur] = min(dp[cur], best);
    if(lo == hi) {
        return;
    }
    solve(lo, mid, ind, best_ind, ub);
    solve(mid + 1, hi, ind, lb, best_ind);
}

void add(int pt, int lo, int hi, int ind) {
    pair<int, int> lo_pt = pts[levels[lev - 1][lo]], hi_pt = pts[levels[lev - 1][hi]];
    if(hi_pt.s > pts[pt].s || lo_pt.f > pts[pt].f) {
        return;
    }
    if(lo_pt.s <= pts[pt].s && hi_pt.f <= pts[pt].f) {
        seg[ind].push_back(pt);
        return;
    }
    int mid = (lo + hi) >> 1;
    add(pt, lo, mid, 2 * ind + 1);
    add(pt, mid + 1, hi, 2 * ind + 2);
}

void dfs(int lo, int hi, int ind) {
    if(!seg[ind].empty()) {
        solve(0, seg[ind].size() - 1, ind, lo, hi);
    }
    seg[ind].clear();
    if(lo == hi) {
        return;
    }
    int mid = (lo + hi) >> 1;
    dfs(lo, mid, 2 * ind + 1);
    dfs(mid + 1, hi, 2 * ind + 2);
}

int main() {
    ifstream cin("mowing.in");
    ofstream cout("mowing.out");
    cin >> n >> t;
    for(int i = 0; i < n; i++) {
        cin >> pts[i + 1].f >> pts[i + 1].s;
    }
    pts[0] = {0, 0}, pts[n + 1] = {t, t}, n += 2;
    sort(pts, pts + n);
    lis.push_back(0), levels[0].push_back(0);
    for(int i = 1; i < n; i++) {
        auto it = upper_bound(lis.begin(), lis.end(), pts[i].s);
        levels[it - lis.begin()].push_back(i), dp[i] = INF;
        if(it == lis.end()) {
            lis.push_back(pts[i].s);
        } else {
            *it = pts[i].s;
        }
    }
    for(int i = 1; i < lis.size(); i++) {
        lev = i;
        for(int p: levels[i]) {
            add(p, 0, levels[i - 1].size() - 1, 0);
        }
        dfs(0, levels[i - 1].size() - 1, 0);
    }
    cout << dp[n - 1] << endl;
}