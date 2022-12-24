#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int sq = 350;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, w; cin >> n >> w;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    int mx_a = *max_element(a.begin(), a.end()), mx_b = *max_element(b.begin(), b.end()), num = n;
    vector<int> lazy(mx_a / sq + 1, 0), ptr(mx_a / sq + 1, 0);
    vector<ll> val(mx_a / sq * sq + sq, 0);
    vector<vector<int>> qu(mx_b + 2);
    vector<vector<pair<int, ll>>> hull(mx_a / sq + 1);
    for(int i = 0; i < n; i++) {
        qu[b[i]].push_back(i);
    }
    for(int i = 0; i < mx_a + 1; i++) {
        hull[i / sq].push_back({i, val[i]});
    }
    auto eval = [](pair<int, ll> line, int coord) { // what it sounds like
        return 1LL * line.f * coord + line.s;
    };
    auto overtakes = [&](int block, pair<int, ll> l3) { // does l3 render the last line of hull[block] useless?
        int sz = hull[block].size();
        pair<int, ll> l1 = hull[block][sz - 2], l2 = hull[block][sz - 1];
        return 1LL * (l1.s - l2.s) * (l3.f - l1.f) >= 1LL * (l1.s - l3.s) * (l2.f - l1.f);
    };
    for(int i = 0; i <= mx_b + 1; i++) { // find global max
        ll pay = 0; int opt = 0;
        for(int j = 0; j <= mx_a / sq; j++) {
            while(ptr[j] + 1 < hull[j].size() && eval(hull[j][ptr[j]], lazy[j]) <= eval(hull[j][ptr[j] + 1], lazy[j])) {
                ++ptr[j];
            }
            pair<int, ll> best_line = hull[j][ptr[j]];
            if(eval(best_line, lazy[j]) > pay) {
                pay = eval(best_line, lazy[j]), opt = best_line.f;
            }
        }
        cout << pay + 1LL * num * i * w << " " << opt << '\n';
        for(int ind: qu[i]) { // add iota up to a[ind] inclusive
            int block = a[ind] / sq;
            for(int j = 0; j < block; j++) {
                ++lazy[j];
            }
            hull[block].clear();
            for(int j = block * sq; j < min(mx_a + 1, block * sq + sq); j++) {
                if(j <= a[ind]) {
                    val[j] += j;
                }
                val[j] += lazy[block] * j;
                while(hull[block].size() > 1 && overtakes(block, {j, val[j]})) {
                    hull[block].pop_back();
                }
                hull[block].push_back({j, val[j]});
            }
            lazy[block] = ptr[block] = 0, --num;
        }
    }
}
