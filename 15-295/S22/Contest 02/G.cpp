#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

template<typename T>
struct FenwickTree {
    size_t n;
    vector<T> amt, bit;

    FenwickTree(size_t n): n(n), amt(n, 0), bit(n, 0) {};

    T qry(int k) {
        T ret = 0;
        for(k++; k > 0; k -= (k & (-k))) {
            ret += bit[k - 1];
        }
        return ret;
    }

    T range_qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }

    void upd(int k, T x) {
        T diff = x - amt[k];
        amt[k] += diff;
        for(k++; k <= n; k += (k & (-k))) {
            bit[k - 1] += diff;
        }
    }
};

int n, q, p[1000000], l[1000000], r[1000000], li[1000000], ri[1000000];
ll ans[1000000];
pair<int, int> lo[1000000], ro[1000000];
vector<int> ct[1000000], lq[1000000], rq[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for(int i = 0; i < q; i++) {
        cin >> l[i];
        --l[i];
        lq[l[i]].push_back(i);
    }
    for(int i = 0; i < q; i++) {
        cin >> r[i];
        --r[i];
        rq[r[i]].push_back(i);
    }
    stack<int> ls, rs;
    FenwickTree<ll> lb(n), rb(n), ld(n), rd(n);
    for(int i = 0; i < n; i++) {
        while(!ls.empty() && p[ls.top()] < p[i]) {
            ls.pop();
        }
        if(ls.empty()) {
            li[i] = -1;
        } else {
            li[i] = ls.top();
        }
        lb.upd(i, li[i] + 1);
        ls.push(i);
        lo[i] = {li[i] + 1, i};
    }
    for(int i = n - 1; i >= 0; i--) {
        while(!rs.empty() && p[rs.top()] < p[i]) {
            rs.pop();
        }
        if(rs.empty()) {
            ri[i] = n;
        } else {
            ri[i] = rs.top();
        }
        rb.upd(i, ri[i] - 1);
        rs.push(i);
        ro[i] = {ri[i] - 1, i};
    }
    sort(lo, lo + n);
    sort(ro, ro + n);
    for(int i = n - 1, j = n - 1; i >= 0; i--) {
        while(j >= 0 && ro[j].f >= i) {
            rb.upd(ro[j].s, 0), rd.upd(ro[j].s, 1);
            --j;
        }
        for(int q: rq[i]) {
            ans[q] += rb.range_qry(l[q], r[q]) + 1LL * i * rd.range_qry(l[q], r[q]);
        }
    }
    for(int i = 0, j = 0; i < n; i++) {
        while(j < n && lo[j].f <= i) {
            lb.upd(lo[j].s, 0), ld.upd(lo[j].s, 1);
            ++j;
        }
        for(int q: lq[i]) {
            ans[q] -= (lb.range_qry(l[q], r[q]) + 1LL * i * ld.range_qry(l[q], r[q]));
        }
    }
    for(int i = 0; i < q; i++) {
        cout << ans[i] + r[i] - l[i] + 1 << " ";
    }
    cout << '\n';
}