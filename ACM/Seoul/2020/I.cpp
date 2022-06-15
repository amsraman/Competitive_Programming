#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 0xfffffffffffffff;

struct FenwickTree2D {
    size_t n;
    vector<vector<ll>> bit;

    FenwickTree2D(size_t n): n(n), bit(n, vector<ll>(n, -INF)) {};

    ll qry(int x, int y) {
        ll ret = -INF;
        for(x++; x > 0; x -= x & -x) {
            for(int i = y + 1; i > 0; i -= i & -i) {
                ret = max(ret, bit[x - 1][i - 1]);
            }
        }
        return ret;
    }

    void upd(int x, int y, ll k) {
        for(x++; x <= n; x += x & -x) {
            for(int i = y + 1; i <= n; i += i & -i) {
                bit[x - 1][i - 1] = max(bit[x - 1][i - 1], k);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<ll> vals(n), ans(m);
    vector<array<ll, 3>> prefix_sums;
    vector<array<ll, 4>> queries(m);
    for(int i = 0; i < n; i++) {
        cin >> vals[i];
        ll cur = 0;
        for(int j = i; j >= 0; j--) {
            cur += vals[j];
            prefix_sums.push_back({cur, j, i});
        }
    }
    for(int i = 0, s, e; i < m; i++) {
        cin >> queries[i][1] >> queries[i][2] >> queries[i][0];
        --queries[i][1], --queries[i][2];
        queries[i][3] = i;
    }
    sort(prefix_sums.begin(), prefix_sums.end());
    sort(queries.begin(), queries.end());
    FenwickTree2D ft(n);
    for(int i = 0, j = 0; i < m; i++) {
        while(j < n * (n + 1) / 2 && prefix_sums[j][0] <= queries[i][0]) {
            ft.upd(n - prefix_sums[j][1] - 1, prefix_sums[j][2], prefix_sums[j][0]);
            j++;
        }
        ans[queries[i][3]] = ft.qry(n - queries[i][1] - 1, queries[i][2]);
    }
    for(ll a: ans) {
        if(a == -INF) {
            cout << "NONE\n";
        } else {
            cout << a << '\n';
        }
    }
}