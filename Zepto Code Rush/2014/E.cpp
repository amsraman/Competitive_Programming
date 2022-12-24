#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const ll INF = 1e16;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, w;
    cin >> n >> w;
    vector<int> num(2 * n, 0), pos(2 * n);
    vector<pair<int, int>> stars(n), ord;
    vector<pair<pair<int, int>, int>> star_ord(n);
    vector<ll> sum(2 * n, 0);
    for(int i = 0; i < n; i++) {
        cin >> star_ord[i].f.s >> star_ord[i].f.f;
        star_ord[i].s = i;
    }
    sort(star_ord.begin(), star_ord.end());
    for(int i = 0; i < n; i++) {
        stars[i] = star_ord[i].f;
        ord.push_back({stars[i].s, i << 1});
        ord.push_back({stars[i].f - stars[i].s, i << 1 ^ 1});
    }
    sort(ord.begin(), ord.end());
    for(int i = 0; i < 2 * n; i++) {
        pos[ord[i].s] = i;
    }
    auto ins = [&](int k) {
        ll add = (k & 1 ? stars[k >> 1].f - stars[k >> 1].s : stars[k >> 1].s);
        for(k = pos[k] + 1; k <= 2 * n; k += k & -k) {
            ++num[k - 1];
            sum[k - 1] += add;
        }
    };
    auto rem = [&](int k) {
        ll sub = (k & 1 ? stars[k >> 1].f - stars[k >> 1].s : stars[k >> 1].s);
        for(k = pos[k] + 1; k <= 2 * n; k += k & -k) {
            --num[k - 1];
            sum[k - 1] -= sub;
        }
    };
    auto k_smallest = [&](int k) {
        ll ret = 0;
        for(int i = 20, j = -1; i >= 0; i--) {
            if((j + (1 << i) < 2 * n) && num[j + (1 << i)] <= k) {
                j += (1 << i);
                k -= num[j];
                ret += sum[j];
            }
        }
        return (k > 0 ? INF : ret);
    };
    for(int i = 0; i < n; i++) {
        ins(i << 1);
    }
    int ind = -1;
    ll ans = k_smallest(w), cur = 0;
    for(int i = 0; i < n; i++) {
        rem(i << 1);
        cur += stars[i].s;
        ll res = cur + stars[i].f - stars[i].s + k_smallest(w - i - 2);
        if(res <= ans) {
            ans = res;
            ind = i;
        }
        ins(i << 1 ^ 1);
    }
    vector<int> res(n);
    set<pair<int, int>> lowest;
    int left = w;
    for(int i = 0; i < n; i++) {
        if(i < ind) {
            res[star_ord[i].s] = 1, --left;
            lowest.insert({stars[i].f - stars[i].s, i});
        } else if(i == ind) {
            res[star_ord[i].s] = 2, left -= 2;
        } else {
            lowest.insert({stars[i].s, i});
        }
    }
    while(left > 0) {
        pair<int, int> cl = *lowest.begin();
        lowest.erase(lowest.begin()), --left;
        ++res[star_ord[cl.s].s];
    }
    cout << ans << '\n';
    for(int i = 0; i < n; i++) {
        cout << res[i];
    }
    cout << '\n';
}