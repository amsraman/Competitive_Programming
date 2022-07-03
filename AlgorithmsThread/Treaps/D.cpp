#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll INF = 0xfffffffffffffff;

struct Node {
    int priority, sz, num;
    ll key, sum, mx1, mx2, lazy;
    Node *l, *r;
    Node(ll key): key(key), priority(rand()), sz(1), mx1(key), mx2(-INF), num(1), sum(key), lazy(0), l(NULL), r(NULL) {};
};
typedef Node* Treap;

array<ll, 3> comb(array<ll, 3> a1, array<ll, 3> a2) {
    if(a1[0] > a2[0]) {
        return {a1[0], max(a1[1], a2[0]), a1[2]};
    } else if(a2[0] > a1[0]) {
        return {a2[0], max(a1[0], a2[1]), a2[2]};
    }
    return {a1[0], max(a1[1], a2[1]), a1[2] + a2[2]};
}

void refresh(Treap t) {
    if(t) {
        t->sz = 1 + (t->l ? t->l->sz : 0) + (t->r ? t->r->sz : 0);
        t->sum = (t->l ? t->l->sum : 0) + (t->r ? t->r->sum : 0) + t->key;
        ll lmx1 = (t->l ? t->l->mx1 : -INF), rmx1 = (t->r ? t->r->mx1 : -INF);
        ll lmx2 = (t->l ? t->l->mx2 : -INF), rmx2 = (t->r ? t->r->mx2 : -INF);
        int lnum = (t->l ? t->l->num : 0), rnum = (t->r ? t->r->num : 0);
        array<ll, 3> res = comb(comb({lmx1, lmx2, lnum}, {t->key, -INF, 1}), {rmx1, rmx2, rnum});
        t->mx1 = res[0], t->mx2 = res[1], t->num = res[2];
    }
}

void min_with(Treap t, ll x) {
    if(t) {
        if(x >= t->mx1) {
            return;
        } else if(x > t->mx2) {
            t->sum += 1LL * t->num * (x - t->mx1), t->key = min(t->key, x), t->mx1 = x;
        }
    }
}

void add(Treap t, ll x) {
    if(t) {
        t->key += x, t->sum += x * t->sz, t->lazy += x;
        t->mx1 += x, t->mx2 = (t->mx2 == -INF ? -INF : t->mx2 + x);
    }
}

void push(Treap t) {
    if(t) {
        add(t->l, t->lazy), add(t->r, t->lazy), t->lazy = 0;
        min_with(t->l, t->mx1), min_with(t->r, t->mx1);
    }
}

void ckmin(Treap t, ll x) {
    if(t) {
        push(t);
        if(x > t->mx2) {
            min_with(t, x);
        } else {
            t->key = min(t->key, x);
            ckmin(t->l, x), ckmin(t->r, x);
            refresh(t);
        }
    }
}

void split(Treap t, int num, Treap & l, Treap & r) {
    push(t);
    if(!t) {
        l = r = NULL;
    } else if((t->l ? t->l->sz : 0) + 1 <= num) {
        split(t->r, num - (t->l ? t->l->sz : 0) - 1, t->r, r), l = t;
    } else {
        split(t->l, num, l, t->l), r = t;
    }
    refresh(t);
}

void join(Treap & t, Treap l, Treap r) {
    push(l), push(r);
    if(!l || !r) {
        t = l ? l : r;
    } else if(l->priority > r->priority) {
        join(l->r, l->r, r), t = l;
    } else {
        join(r->l, l, r->l), t = r;
    }
    refresh(t);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    Treap t = NULL, p1, p2;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        join(t, t, new Node(a[i]));
    }
    for(int i = 0, tp, l, r, h, x; i < q; i++) {
        cin >> tp >> l >> r;
        split(t, l - 1, p1, t), split(t, r - l + 1, p2, t);
        if(tp == 1) {
            cin >> h;
            ckmin(p2, h);
            join(t, p2, t), join(t, p1, t);
        } else if(tp == 2) {
            join(t, t, p2), join(t, p1, t);
        } else {
            cin >> x;
            add(p2, x);
            join(t, p2, t), join(t, p1, t);
        }
        cout << t->sum << '\n';
    }
}