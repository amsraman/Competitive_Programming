#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ifstream cin("pay_off_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, q, l; cin >> n >> q >> l;
        vector<int> x(n);
        for(int i = 0; i < n; i++) {
            cin >> x[i]; x[i] = l + 1 - x[i];
        }
        ll tot = 0; set<int> walls;
        walls.insert(1); walls.insert(l);
        vector<set<ll>> fw(n); map<int, int> at_val;
        for(int i = 0; i < n; i++) {
            at_val[x[i]] = i;
            for(int ind = i + 1; ind <= n; ind += ind & -ind) {
                fw[ind - 1].insert(x[n - i - 1]);
            }
        }
        for(int i = 0, tp; i < q; i++) {
            cin >> tp;
            if(tp == 1) {
                int x; cin >> x; x = l + 1 - x;
                walls.insert(x);
            } else {
                int r, s; cin >> r >> s; --r;
                int lb = *prev(walls.lower_bound(x[r])), ub = *walls.lower_bound(x[r]);
                int len = ub - lb, prev = 0, cur1 = 0, cur2 = 0, md = s % (2 * len);
                for(int ind = n - r - 1; ind > 0; ind -= ind & -ind) {
                    auto it = fw[ind - 1].lower_bound(lb);
                    if(it != fw[ind - 1].end() && *it < ub && (prev == 0 || *it < x[prev - 1])) {
                        prev = at_val[*it] + 1;
                    }
                    ll use = max(1LL * lb, 2LL * ub - 2LL * md - x[r]);
                    it = fw[ind - 1].lower_bound(use);
                    if(it != fw[ind - 1].end() && *it < ub && (cur1 == 0 || *it < x[cur1 - 1])) {
                        cur1 = at_val[*it] + 1;
                    }
                    use = max(1LL * lb, 2LL * ub - 2LL * md - x[r] + 2LL * len);
                    it = fw[ind - 1].lower_bound(use);
                    if(it != fw[ind - 1].end() && *it < ub && (cur2 == 0 || *it < x[cur2 - 1])) {
                        cur2 = at_val[*it] + 1;
                    }
                }
                if(cur2 == 0) cur2 = cur1;
                if(cur2 == 0 && s >= 2 * len) cur2 = prev;
                tot += cur2;
            }
        }
        cout << "Case #" << _ << ": " << tot << '\n';
    }
}
/*
phase 1: (ub - x) - ((y - x) / 2) <= tm
    <=> 2 * (ub - x) - (y - x) <= 2 * tm
    <=> 2 * ub - x - y <= 2 * tm
    <=> y >= 2 * ub - x - 2 * tm

phase 2: (ub - x) + ((x - y) / 2) <= tm
    <=> 2 * (ub - x) + (x - y) <= 2 * tm
    <=> 2 * ub - x - y <= 2 * tm
    <=> y >= 2 * ub - 2 * tm - x
*/