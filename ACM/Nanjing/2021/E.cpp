#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int mod = 1e9 + 7;

int n, m, q, a[50000];
array<array<int, 4>, 4> id = {array<int, 4>{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
vector<array<int, 4>> seg;
vector<array<array<int, 4>, 4>> lazy;

void bld(int lo, int hi, int ind) {
    if(lo == hi) {
        int sq = (1LL * a[lo] * a[lo]) % mod;
        seg[ind] = {sq, sq, a[lo], 1};
        return;
    }
    int mid = (lo + hi) >> 1;
    bld(lo, mid, 2 * ind + 1);
    bld(mid + 1, hi, 2 * ind + 2);
    for(int i = 0; i < 4; i++) {
        seg[ind][i] = seg[2 * ind + 1][i] + seg[2 * ind + 2][i];
        if(seg[ind][i] >= mod) {
            seg[ind][i] -= mod;
        }
    }
}

void app(int ind, array<array<int, 4>, 4> delta) {
    array<int, 4> new_vec;
    array<array<int, 4>, 4> new_mat;
    for(int i = 0; i < 4; i++) {
        new_vec[i] = 0;
        new_mat[i].fill(0);
        for(int j = 0; j < 4; j++) {
            new_vec[i] += (1LL * seg[ind][j] * delta[i][j]) % mod;
            if(new_vec[i] >= mod) {
                new_vec[i] -= mod;
            }
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = i; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                new_mat[i][j] += (1LL * delta[i][k] * lazy[ind][k][j]) % mod;
                if(new_mat[i][j] >= mod) {
                    new_mat[i][j] -= mod;
                }
            }
        }
    }
    seg[ind] = new_vec, lazy[ind] = new_mat;
}

void push(int ind, int lo, int hi) {
    if(lazy[ind] == id) {
        return;
    }
    if(lo != hi) {
        app(2 * ind + 1, lazy[ind]);
        app(2 * ind + 2, lazy[ind]);
    }
    lazy[ind] = id;
}

int qry(int lo, int hi, int lo_ind, int hi_ind, int ind) {
    if(lo <= lo_ind && hi_ind <= hi) {
        return seg[ind][0];
    }
    int mid = (lo_ind + hi_ind) >> 1;
    push(ind, lo_ind, hi_ind);
    int res = (lo <= mid ? qry(lo, hi, lo_ind, mid, 2 * ind + 1) : 0);
    res += (hi > mid ? qry(lo, hi, mid + 1, hi_ind, 2 * ind + 2) : 0);
    if(res >= mod) {
        res -= mod;
    }
    return res;
}

void upd(int lo, int hi, int delta, int lo_ind, int hi_ind, int ind) {
    if(lo > hi) {
        return;
    }
    if(lo <= lo_ind && hi_ind <= hi) {
        array<array<int, 4>, 4> mat;
        int dd = (2 * delta) % mod, sq = (1LL * delta * delta) % mod;
        mat = {array<int, 4>{1, 1, dd, sq}, {0, 1, dd, sq}, {0, 0, 1, delta}, {0, 0, 0, 1}};
        app(ind, mat);
        return;
    }
    int mid = (lo_ind + hi_ind) >> 1;
    push(ind, lo_ind, hi_ind);
    if(lo <= mid) {
        upd(lo, hi, delta, lo_ind, mid, 2 * ind + 1);
    }
    if(hi > mid) {
        upd(lo, hi, delta, mid + 1, hi_ind, 2 * ind + 2);
    }
    for(int i = 0; i < 4; i++) {
        seg[ind][i] = seg[2 * ind + 1][i] + seg[2 * ind + 2][i];
        if(seg[ind][i] >= mod) {
            seg[ind][i] -= mod;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> q;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] < 0) {
            a[i] += mod;
        }
    }
    vector<array<int, 3>> mods(m);
    vector<vector<array<int, 4>>> qrs(m + 1);
    vector<int> ans(q, 0);
    seg.resize((1 << 17), {0, 0, 0, 0});
    lazy.resize((1 << 17), id);
    for(int i = 0; i < m; i++) {
        cin >> mods[i][0] >> mods[i][1] >> mods[i][2];
        if(mods[i][2] < 0) {
            mods[i][2] += mod;
        }
    }
    for(int i = 0; i < q; i++) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        if(x > 0) {
            qrs[x - 1].push_back({l - 1, r - 1, mod - 1, i});
        }
        qrs[y].push_back({l - 1, r - 1, 1, i});
    }
    bld(0, n - 1, 0);
    for(int i = 0; i <= m; i++) {
        if(i > 0) {
            upd(0, mods[i - 1][0] - 2, 0, 0, n - 1, 0);
            upd(mods[i - 1][0] - 1, mods[i - 1][1] - 1, mods[i - 1][2], 0, n - 1, 0);
            upd(mods[i - 1][1], n - 1, 0, 0, n - 1, 0);
        }
        for(array<int, 4> q: qrs[i]) {
            ans[q[3]] = (ans[q[3]] + (1LL * q[2] * qry(q[0], q[1], 0, n - 1, 0)) % mod) % mod;
        }
    }
    for(int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}