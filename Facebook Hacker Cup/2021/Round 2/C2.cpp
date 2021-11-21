#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

template<class B>
struct LazySegTree : public B {
    using T_q = typename B::T_q;
    using T_u = typename B::T_u;

    size_t n;
    vector<T_q> seg;
    vector<T_u> lazy;

    LazySegTree(size_t n): n(n), seg(2 * n, B::e_q), lazy(2 * n, B::e_u) {};

    void push(int ind, int lo, int hi) {
        seg[ind] = B::upd(seg[ind], lazy[ind], lo, hi);
        if(lo != hi) {
            lazy[2 * ind + 1] = B::comb_upd(lazy[2 * ind + 1], lazy[ind]);
            lazy[2 * ind + 2] = B::comb_upd(lazy[2 * ind + 2], lazy[ind]);
        }
        lazy[ind] = B::e_u;
    }

    T_q qry(int lo, int hi, int lo_ind, int hi_ind, int ind) {
        push(ind, lo_ind, hi_ind);
        if(lo > hi_ind || hi < lo_ind) {
            return B::e_q;
        }
        if(lo <= lo_ind && hi_ind <= hi) {
            return seg[ind];
        }
        int mid = (lo_ind + hi_ind) / 2;
        return B::comb(qry(lo, hi, lo_ind, mid, 2 * ind + 1), qry(lo, hi, mid + 1, hi_ind, 2 * ind + 2));
    }

    T_q qry(int lo, int hi) {
        return qry(lo, hi, 0, n - 1, 0);
    }

    void upd(int lo, int hi, T_u delta, int lo_ind, int hi_ind, int ind) {
        push(ind, lo_ind, hi_ind);
        if(lo > hi_ind || hi < lo_ind) {
            return;
        }
        if(lo <= lo_ind && hi_ind <= hi) {
            lazy[ind] = delta;
            push(ind, lo_ind, hi_ind);
            return;
        }
        int mid = (lo_ind + hi_ind) / 2;
        upd(lo, hi, delta, lo_ind, mid, 2 * ind + 1);
        upd(lo, hi, delta, mid + 1, hi_ind, 2 * ind + 2);
        seg[ind] = B::comb(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void upd(int lo, int hi, T_u delta) {
        return upd(lo, hi, delta, 0, n - 1, 0);
    }
};

struct MinLL {
    using T_q = ll;
    const T_q e_q = 0x3f3f3f3f;

    using T_u = ll;
    const T_u e_u = 0;

    T_q comb(T_q a, T_q b) {
        return min(a, b);
    }

    T_q upd(T_q a, T_u b, int l, int r) {
        return a + b;
    }

    T_u comb_upd(T_u a, T_u b) {
        return a + b;
    }
};

int t, r, c, k, s, up_kth[2000000], init_size, mn[2000000];
vector<pair<int, int>> mvs;
string grid[2000000];

void solve() {
    memset(up_kth, -1, sizeof(up_kth));
    LazySegTree<MinLL> up(1 << 21);
    vector<set<int>> up_set(c);
    for(int i = 0; i <= r + 1; i++) {
        up.upd(i, i, i - 0x3f3f3f3f);
    }
    for(int i = 0; i < mvs.size(); i++) {
        int a = mvs[i].f, b = mvs[i].s;
        if(grid[a][b] == 'X') {
            if(up_kth[b] == -1) {
                if(a >= k - 1) {
                    up.upd(a - k + 1, a - k + 1, -1);
                }
                up_set[b].erase(a);
            } else if(a <= up_kth[b]) {
                if(a >= k - 1) {
                    up.upd(a - k + 1, a - k + 1, -1);
                }
                up_set[b].erase(a);
                up.upd(up_kth[b] - k + 2, r + 1, -1);
                if(up_set[b].size() >= k) {
                    int pv = up_kth[b];
                    up_kth[b] = *(up_set[b].upper_bound(up_kth[b]));
                    up.upd(up_kth[b] - k + 1, r + 1, 1);
                } else {
                    up_kth[b] = -1;
                }
            } else {
                up_set[b].erase(a);
            }
            grid[a][b] = '.';
        } else {
            if(up_kth[b] == -1) {
                if(a >= k - 1) {
                    up.upd(a - k + 1, a - k + 1, 1);
                }
                up_set[b].insert(a);
                if(up_set[b].size() == k) {
                    up_kth[b] = *(--up_set[b].end());
                    up.upd(up_kth[b] - k + 2, r + 1, 1);
                }
            } else if(a < up_kth[b]) {
                if(a >= k - 1) {
                    up.upd(a - k + 1, a - k + 1, 1);
                }
                up_set[b].insert(a);
                up.upd(up_kth[b] - k + 1, r + 1, -1);
                up_kth[b] = *(--up_set[b].find(up_kth[b]));
                up.upd(up_kth[b] - k + 2, r + 1, 1);
            } else {
                up_set[b].insert(a);
            }
            grid[a][b] = 'X';
        }
        if(i >= init_size) {
            mn[i - init_size] = min(mn[i - init_size], (int) up.qry(0, r + 1));
        }
    }
}

int main() {
    freopen("valet_parking_chapter_2_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> r >> c >> k >> s;
        for(int i = 0; i < r; i++) {
            cin >> grid[i];
        }
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(grid[i][j] == 'X') {
                    mvs.push_back({i, j});
                    grid[i][j] = '.';
                }
            }
        }
        init_size = mvs.size();
        for(int i = 0, a, b; i < s; i++) {
            cin >> a >> b;
            mvs.push_back({a - 1, b - 1});
            mn[i] = 0x3f3f3f3f;
        }
        ll ans = 0;
        solve();
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                grid[i][j] = '.';
            }
        }
        for(int i = 0; i < mvs.size(); i++) {
            mvs[i].f = r - mvs[i].f - 1;
        }
        k = r - k + 1;
        solve();
        for(int i = 0; i < s; i++) {
            ans += mn[i];
        }
        cout << "Case #" << _ << ": " << ans << endl;
        mvs.clear();
    }
}