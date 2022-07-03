#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

struct Node {
    int key, priority, sz;
    ll val, sum;
    Node *l, *r, *p;
    Node(int key, ll val): key(key), val(val), priority(rand()), sz(1), sum(val), l(NULL), r(NULL), p(NULL) {};
    Node(int key, ll val, int priority): key(key), val(val), priority(priority), sz(1), sum(val), l(NULL), r(NULL), p(NULL) {};
};
typedef Node* Treap;

void refresh(Treap t) {
    if(t) {
        t->sz = 1 + (t->l ? t->l->sz : 0) + (t->r ? t->r->sz : 0);
        t->sum = t->val + (t->l ? t->l->sum : 0) + (t->r ? t->r->sum : 0);
        if(t->l) {
            t->l->p = t;
        }
        if(t->r) {
            t->r->p = t;
        }
        t->p = NULL;
    }
}

void split(Treap t, int num, Treap & l, Treap & r) {
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
    int q;
    cin >> q;
    vector<Treap> nodes(5e5 + 1);
    for(int i = 0, t, y, z; i < q; i++) {
        cin >> t >> y;
        if(t == 1) {
            nodes[i + 1] = new Node(i + 1, y);
        } else if(t == 2) {
            cin >> z;
            Treap ty = nodes[y], tz = nodes[z];
            while(ty->p != NULL) {
                ty = ty->p;
            }
            while(tz->p != NULL) {
                tz = tz->p;
            }
            if(ty->key != tz->key) {
                join(ty, ty, tz);
            }
        } else if(t == 3) {
            cin >> z;
            Treap ty = nodes[y], l, r;
            while(ty->p != NULL) {
                ty = ty->p;
            }
            if(ty->sz > z) {
                split(ty, z, l, r);
            }
        } else {
            Treap ty = nodes[y];
            while(ty->p != NULL) {
                ty = ty->p;
            }
            cout << ty->sum << '\n';
        }
    }
}