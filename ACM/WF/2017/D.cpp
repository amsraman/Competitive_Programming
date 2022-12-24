#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, m;
ll ans;
pair<int, int> prod[500000], cons[500000];
vector<pair<int, int>> fp, fc;

void dnc(int lb, int ub, int lo, int hi) {
    int mid = (lb + ub) / 2, opt = lo;
    for(int i = lo; i <= hi; i++) {
        if(1LL * (fc[mid].f - fp[i].f) * (fc[mid].s - fp[i].s) > 1LL * (fc[mid].f - fp[opt].f) * (fc[mid].s - fp[opt].s)) {
            opt = i;
        }
    }
    if(fc[mid].f >= fp[opt].f) {
        ans = max(ans, 1LL * 1LL * (fc[mid].f - fp[opt].f) * (fc[mid].s - fp[opt].s));
    }
    if(lb == ub) return;
    dnc(lb, mid, lo, opt);
    dnc(mid + 1, ub, opt, hi);
}

int main() {
    cin >> m >> n;
    for(int i = 0; i < m; i++) {
        cin >> prod[i].s >> prod[i].f;
    }
    for(int i = 0; i < n; i++) {
        cin >> cons[i].s >> cons[i].f;
    }
    sort(prod, prod + m); sort(cons, cons + n);
    reverse(prod, prod + m);
    for(int i = 0; i < m; i++) {
        while(!fp.empty() && fp.back().f >= prod[i].s) {
            fp.pop_back();
        }
        fp.push_back({prod[i].s, prod[i].f});
    }
    for(int i = 0; i < n; i++) {
        while(!fc.empty() && fc.back().f <= cons[i].s) {
            fc.pop_back();
        }
        fc.push_back({cons[i].s, cons[i].f});
    }
    reverse(fc.begin(), fc.end());
    m = fp.size(); n = fc.size();
    dnc(0, n - 1, 0, m - 1);
    cout << ans << endl;
}