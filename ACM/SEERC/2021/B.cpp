#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <class B>
struct PersistentSegTree : public B {
    using T_q = typename B::T_q;
    using T_u = typename B::T_u;
    struct Node {
        T_q val; T_u lazy;
        Node *left, *right;
        Node(T_q val): val(val), lazy(B::e_u), left(NULL), right(NULL) {};
        Node(T_q val, T_u lazy): val(val), lazy(lazy), left(NULL), right(NULL) {};
        Node(T_q val, T_u lazy, Node *left, Node *right): val(val), lazy(lazy), left(left), right(right) {};
    };
    int n;
    vector<Node*> roots;
    PersistentSegTree(const vector<T_q> & init): n((int) init.size()) {
        roots.push_back(bld(init, 0, n - 1));
    };
    Node* bld(const vector<T_q> & init, int lo, int hi) {
        if(lo == hi) {
            return new Node(init[lo]);
        }
        int mid = lo + (hi - lo) / 2;
        Node *left_child = bld(init, lo, mid), *right_child = bld(init, mid + 1, hi);
        return new Node(B::comb(left_child->val, right_child->val), B::e_u, left_child, right_child);
    }
    Node* app(Node *cur, T_u delta, int lo, int hi) {
        return new Node(B::upd(cur->val, delta, lo, hi), B::comb_upd(delta, cur->lazy), cur->left, cur->right);
    }
    void push(Node *cur, int lo, int hi) {
        if(lo != hi) {
            int mid = lo + (hi - lo) / 2;
            cur->left = app(cur->left, cur->lazy, lo, mid);
            cur->right = app(cur->right, cur->lazy, mid + 1, hi);
        }
        cur->lazy = B::e_u;
    }
    T_q qry(Node *cur, int lo, int hi, int lo_ind, int hi_ind) {
        if(lo <= lo_ind && hi_ind <= hi) {
            return cur->val;
        }
        int mid = lo_ind + (hi_ind - lo_ind) / 2;
        if(cur->lazy != B::e_u) push(cur, lo_ind, hi_ind);
        T_q op1 = (lo <= mid ? qry(cur->left, lo, hi, lo_ind, mid) : B::e_q);
        T_q op2 = (mid < hi ? qry(cur->right, lo, hi, mid + 1, hi_ind) : B::e_q);
        return B::comb(op1, op2);
    }
    Node* upd(Node *cur, int lo, int hi, int lo_ind, int hi_ind, T_u delta) {
        if(lo <= lo_ind && hi_ind <= hi) {
            return app(cur, delta, lo_ind, hi_ind);
        }
        int mid = lo_ind + (hi_ind - lo_ind) / 2;
        if(cur->lazy != B::e_u) push(cur, lo_ind, hi_ind);
        Node *res_left = cur->left, *res_right = cur->right;
        if(lo <= mid) res_left = upd(cur->left, lo, hi, lo_ind, mid, delta);
        if(mid < hi) res_right = upd(cur->right, lo, hi, mid + 1, hi_ind, delta);
        return new Node(B::comb(res_left->val, res_right->val), B::e_u, res_left, res_right);
    }
    T_q qry(int version, int lo, int hi) {
        return qry(roots[version], lo, hi, 0, n - 1);
    }
    void upd(int version, int lo, int hi, T_u delta) {
        roots.push_back(upd(roots[version], lo, hi, 0, n - 1, delta));
    }
};

int k, n, q;

struct SegInfo {
    using T_q = array<ll, 16>;
    using T_u = array<pair<ll, bool>, 4>;
    static constexpr T_q e_q = {LLONG_MAX, LLONG_MAX, LLONG_MAX, LLONG_MAX,
                                LLONG_MAX, LLONG_MAX, LLONG_MAX, LLONG_MAX,
                                LLONG_MAX, LLONG_MAX, LLONG_MAX, LLONG_MAX,
                                LLONG_MAX, LLONG_MAX, LLONG_MAX, LLONG_MAX};
    static constexpr T_u e_u = {pair<ll, bool>{0LL, false}, {0LL, false}, {0LL, false}, {0LL, false}};
    T_q comb(T_q a, T_q b) {
        for(int i = 0; i < (1 << k); i++) {
            a[i] = min(a[i], b[i]);
        }
        return a;
    }
    T_q upd(T_q a, T_u b, int l, int r) {
        int msk = 0;
        for(int i = 0; i < k; i++) {
            if(b[i].second) {
                msk ^= (1 << i);
            }
        }
        for(int i = 0; i < (1 << k); i++) {
            a[i] = a[i & (~msk)];
            for(int j = 0; j < k; j++) {
                if((msk & (1 << j)) && (i & (1 << j))) {
                    a[i] += b[j].first;
                }
            }
        }
        for(int i = 0; i < (1 << k); i++) {
            for(int j = 0; j < k; j++) {
                if(!b[j].second && (i & (1 << j))) {
                    a[i] += b[j].first;
                }
            }
        }
        return a;
    }
    T_u comb_upd(T_u a, T_u b) {
        // a after b
        for(int i = 0; i < k; i++) {
            if(a[i].second) {
                continue;
            } else if(b[i].second) {
                a[i].first += b[i].first, a[i].second = true;
            } else {
                a[i].first += b[i].first;
            }
        }
        return a;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> k >> n >> q;
    vector<array<ll, 16>> a(n);
    for(int i = 0; i < n; i++) a[i].fill(0LL);
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[j][(1 << i)];
        }
    }
    vector<array<ll, 16>> tot(n);
    for(int i = 0; i < n; i++) {
        for(int j = 1; j < (1 << k); j++) {
            int lsb = (j & -j);
            a[i][j] = a[i][lsb] + a[i][j ^ lsb];
        }
    }
    PersistentSegTree<SegInfo> pst(a);
    vector<int> version(q + 1, 0);
    for(int i = 0, type; i < q; i++) {
        cin >> type;
        version[i + 1] = version[i];
        if(type == 1) {
            int t, p, l, r, x;
            cin >> t >> p >> l >> r >> x;
            --p, --l, --r;
            array<pair<ll, bool>, 4> delta; delta.fill({0LL, false});
            delta[p] = {x, false};
            pst.upd(version[t], l, r, delta);
            ++version[i + 1];
        } else if(type == 2) {
            int t, p, l, r, y;
            cin >> t >> p >> l >> r >> y;
            --p, --l, --r;
            array<pair<ll, bool>, 4> delta; delta.fill({0LL, false});
            delta[p] = {y, true};
            pst.upd(version[t], l, r, delta);
            ++version[i + 1];
        } else {
            int t, l, r;
            cin >> t >> l >> r;
            --l, --r;
            array<ll, 16> res = pst.qry(version[t], l, r);
            cout << res[(1 << k) - 1] << '\n';
        }
    }
}