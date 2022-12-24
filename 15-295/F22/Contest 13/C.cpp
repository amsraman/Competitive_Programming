#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int sq = 350;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n), b(n), a_ord(n), b_coords;
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        b_coords.push_back(b[i]);
    }
    iota(a_ord.begin(), a_ord.end(), 0);
    sort(a_ord.begin(), a_ord.end(), [&](int i, int j) {
         return a[i] < a[j];
    });
    sort(b_coords.begin(), b_coords.end());
    b_coords.erase(unique(b_coords.begin(), b_coords.end()), b_coords.end());
    int b_sz = b_coords.size();
    vector<int> lazy((b_sz - 2) / sq + 1, 0), ptr((b_sz - 2) / sq + 1, 0);
    vector<ll> val((b_sz - 2) / sq * sq + sq, 0);
    vector<vector<pair<int, ll>>> hull((b_sz - 2) / sq + sq);
    for(int i = 0; i < b_coords.size(); i++) {
        hull[i / sq].push_back({b_coords[i], val[i]});
    }
    auto eval = [](pair<int, ll> line, int coord) { // what it sounds like
        return 1LL * line.f * coord + line.s;
    };
    auto overtakes = [&](int block, pair<int, ll> l3) { // does l3 render the last line of hull[block] useless?
        int sz = hull[block].size();
        pair<int, ll> l1 = hull[block][sz - 2], l2 = hull[block][sz - 1];
        return 1LL * (l1.s - l2.s) * (l3.f - l1.f) >= 1LL * (l1.s - l3.s) * (l2.f - l1.f);
    };
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        if(i == 0 || a[a_ord[i]] != a[a_ord[i - 1]]) { // find global max at each point
            for(int j = 0; j <= (b_sz - 2) / sq; j++) {
                while(ptr[j] + 1 < hull[j].size() && eval(hull[j][ptr[j]], lazy[j]) <= eval(hull[j][ptr[j] + 1], lazy[j])) {
                    ++ptr[j];
                }
                pair<int, ll> best_line = hull[j][ptr[j]];
                ans = max(ans, 1LL * (n - i) * a[a_ord[i]] + eval(best_line, lazy[j]));
            }
        }
        int ind = lower_bound(b_coords.begin(), b_coords.end(), b[a_ord[i]]) - b_coords.begin(), block = ind / sq;
        for(int j = 0; j < block; j++) {
            ++lazy[j];
        }
        hull[block].clear();
        for(int j = block * sq; j < min(b_sz, block * sq + sq); j++) {
            if(j <= ind) {
                val[j] += b_coords[j];
            }
            val[j] += 1LL * lazy[block] * b_coords[j];
            while(hull[block].size() > 1 && overtakes(block, {b_coords[j], val[j]})) {
                hull[block].pop_back();
            }
            hull[block].push_back({b_coords[j], val[j]});
        }
        lazy[block] = ptr[block] = 0;
    }
    sort(b.begin(), b.end()); // case where p >> max(A)
    for(int i = 0; i < n; i++) {
        ans = max(ans, 1LL * (n - i) * b[i]);
    }
    cout << ans << '\n';
}
