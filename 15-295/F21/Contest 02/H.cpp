#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int sq = 350;

template<typename T>
struct FenwickTree {
    int n;
    vector<T> bit;

    FenwickTree(int n): n(n), bit(n, 0) {};

    T qry(int x) {
        T ret = 0;
        for(x++; x > 0; x -= (x & -x)) {
            ret += bit[x - 1];
        }
        return ret;
    }

    T qry(int x, int y) {
        return qry(y) - qry(x - 1);
    }

    void upd(int x, T k) {
        for(x++; x <= n; x += (x & -x)) {
            bit[x - 1] += k;
        }
    }
};

int n, m, q, a[30000], val[30000], pos[30000], cur = -1, num[30000], fibs[30002], seg1[1 << 16], seg2[1 << 16], lazy[(1 << 16)], ans[30000]; 
array<int, 2> ord[30000];
array<int, 4> qrs[30000];

int add(int x, int y) {
    return (x + y >= m ? x + y - m : x + y);
}

int get_fib(int ind) {
    if(ind < 0) {
        return ((ind & 1 ^ 1) ? m - fibs[-ind] : fibs[-ind]);
    }
    return fibs[ind];
}

void push(int ind, int lo, int hi) {
    int delta = lazy[ind], cur_term = seg1[ind], pv_term = seg2[ind];
    seg1[ind] = (1LL * get_fib(delta + 1) * cur_term + 1LL * get_fib(delta) * pv_term) % m;
    seg2[ind] = (1LL * get_fib(delta) * cur_term + 1LL * get_fib(delta - 1) * pv_term) % m;
    if(lo != hi) {
        lazy[2 * ind + 1] += delta;
        lazy[2 * ind + 2] += delta;
    }
    lazy[ind] = 0;
}

void upd(int lo, int delta, int lo_ind, int hi_ind, int ind, bool on) {
    if(lo < lo_ind) {
        lazy[ind] += (on ? 1 : -1);
        push(ind, lo_ind, hi_ind);
        return;
    }
    if(lazy[ind] != 0) {
        push(ind, lo_ind, hi_ind);
    }
    if(lo > hi_ind) {
        return;
    }
    if(lo_ind == hi_ind) {
        seg1[ind] = (1LL * get_fib(delta + 1) * (on ? val[lo_ind] : 0)) % m;
        seg2[ind] = (1LL * get_fib(delta) * (on ? val[lo_ind] : 0)) % m;
        return;
    }
    int mid = (lo_ind + hi_ind) / 2;
    upd(lo, delta, lo_ind, mid, 2 * ind + 1, on);
    upd(lo, delta, mid + 1, hi_ind, 2 * ind + 2, on);
    seg1[ind] = add(seg1[2 * ind + 1], seg1[2 * ind + 2]);
    seg2[ind] = add(seg2[2 * ind + 1], seg2[2 * ind + 2]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    FenwickTree<int> ft(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ord[i] = {a[i], i};
    }
    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> qrs[i][2] >> qrs[i][1];
        --qrs[i][2], --qrs[i][1];
        qrs[i][0] = qrs[i][2] / sq, qrs[i][3] = i;
    }
    sort(ord, ord + n);
    sort(qrs, qrs + q);
    for(int i = 0; i < n; i++) {
        if(i == 0 || ord[i][0] != ord[i - 1][0]) {
            val[++cur] = ord[i][0];
        }
        pos[ord[i][1]] = cur;
    }
    fibs[1] = 1;
    for(int i = 2; i <= n + 1; i++) {
        fibs[i] = add(fibs[i - 1], fibs[i - 2]);
    }
    n = cur;
    for(int i = 0, l = 0, r = -1; i < q; i++) {
        int left_point = qrs[i][2], right_point = qrs[i][1], ind;
        while(l > left_point) {
            --l, ind = pos[l];
            if(num[ind] == 0) {
                upd(ind, ft.qry(pos[l]), 0, (1 << 15) - 1, 0, true);
                ft.upd(ind, 1);
            }
            ++num[ind];
        }
        while(r < right_point) {
            ++r, ind = pos[r];
            if(num[ind] == 0) {
                upd(ind, ft.qry(ind), 0, (1 << 15) - 1, 0, true);
                ft.upd(ind, 1);
            }
            ++num[ind];
        }
        while(l < left_point) {
            ind = pos[l], --num[ind];
            if(num[ind] == 0) {
                upd(ind, 0, 0, (1 << 15) - 1, 0, false);
                ft.upd(ind, -1);
            }
            ++l;
        }
        while(r > right_point) {
            ind = pos[r], --num[ind];
            if(num[ind] == 0) {
                upd(ind, 0, 0, (1 << 15) - 1, 0, false);
                ft.upd(ind, -1);
            }
            --r;
        }
        ans[qrs[i][3]] = seg1[0];
    }
    for(int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}