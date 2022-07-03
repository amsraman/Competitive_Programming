#include <bits/stdc++.h>

using namespace std;

struct Node {
    char key;
    int num_zeros, num_ones, zp, zs, op, os, mx, priority, sz;
    int ind;
    bool flip, rev, set_zero, set_one;
    Node *l, *r;
    Node(char key, int ind): key(key), ind(ind), mx(1), priority(rand()), sz(1), l(NULL), r(NULL) {
        if(key == '0') {
            zp = zs = num_zeros = 1, op = os = num_ones = 0;
        } else {
            op = os = num_ones = 1, zp = zs = num_zeros = 0;
        }
        flip = rev = set_zero = set_one = false;
    };
};
typedef Node* Treap;

void flip(Treap t) {
    if(t) {
        swap(t->zp, t->op), swap(t->zs, t->os), swap(t->num_zeros, t->num_ones);
        t->key ^= ('0' ^ '1'), t->flip ^= 1;
        if(t->set_zero) {
            t->set_zero = false, t->set_one = true;
        } else if(t->set_one) {
            t->set_one = false, t->set_zero = true;
        }
    }
}

void rev(Treap t) {
    if(t) {
        swap(t->op, t->os), swap(t->zp, t->zs), swap(t->l, t->r);
        t->rev ^= 1;
    }
}

void set_zero(Treap t) {
    if(t) {
        t->set_zero = true, t->set_one = t->flip = t->rev = false;
        t->zp = t->zs = t->mx = t->num_zeros = t->sz;
        t->op = t->os = t->num_ones = 0;
        t->key = '0';
    }
}

void set_one(Treap t) {
    if(t) {
        t->set_one = true, t->set_zero = t->flip = t->rev = false;
        t->op = t->os = t->mx = t->num_ones = t->sz;
        t->zp = t->zs = t->num_zeros = 0;
        t->key = '1';
    }
}

void refresh(Treap t) {
    if(t) {
        int lsz = (t->l ? t->l->sz : 0), rsz = (t->r ? t->r->sz : 0);
        int lzp = (t->l ? t->l->zp : 0), rzp = (t->r ? t->r->zp : 0);
        int lzs = (t->l ? t->l->zs : 0), rzs = (t->r ? t->r->zs : 0);
        int lop = (t->l ? t->l->op : 0), rop = (t->r ? t->r->op : 0);
        int los = (t->l ? t->l->os : 0), ros = (t->r ? t->r->os : 0);
        int lmx = (t->l ? t->l->mx : 0), rmx = (t->r ? t->r->mx : 0);
        int lnz = (t->l ? t->l->num_zeros : 0), rnz = (t->r ? t->r->num_zeros : 0);
        int lno = (t->l ? t->l->num_ones : 0), rno = (t->r ? t->r->num_ones : 0);
        // Combine
        t->sz = 1 + lsz + rsz;
        t->zp = lzp, t->zs = rzs, t->op = lop, t->os = ros;
        t->mx = max(lmx, rmx);
        if(t->key == '0') {
            t->zp = max(t->zp, (lnz == lsz ? lsz + 1 + rzp : 0));
            t->zs = max(t->zs, (rnz == rsz ? rsz + 1 + lzs : 0));
            t->mx = max(t->mx, 1 + lzs + rzp);
        } else {
            t->op = max(t->op, (lno == lsz ? lsz + 1 + rop : 0));
            t->os = max(t->os, (rno == rsz ? rsz + 1 + los : 0));
            t->mx = max(t->mx, 1 + los + rop);
        }
        t->num_zeros = (t->key == '0') + lnz + rnz, t->num_ones = (t->key == '1') + lno + rno;
    }
}

void push(Treap t) {
    if(t) {
        if(t->flip) {
            flip(t->l), flip(t->r), t->flip = false;
        }
        if(t->rev) {
            rev(t->l), rev(t->r), t->rev = false;
        }
        if(t->set_zero) {
            set_zero(t->l), set_zero(t->r), t->set_zero = false;
        }
        if(t->set_one) {
            set_one(t->l), set_one(t->r), t->set_one = false;
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
    string s;
    cin >> n >> q >> s;
    Treap t = NULL, p1, p2, p3;
    for(int i = 0; i < n; i++) {
        join(t, t, new Node(s[i], i));
    }
    for(int i = 0, tp, l, r; i < q; i++) {
        cin >> tp >> l >> r;
        if(tp == 1) {
            split(t, l - 1, p1, t), split(t, r - l + 1, p2, t);
            flip(p2);
            join(t, p2, t), join(t, p1, t);
        } else if(tp == 2) {
            split(t, l - 1, p1, t), split(t, r - l + 1, p2, t);
            rev(p2);
            join(t, p2, t), join(t, p1, t);
        } else {
            split(t, l - 1, p1, t), split(t, r - l + 1, p2, t);
            int num = p2->num_zeros;
            split(p2, num, p2, p3);
            set_zero(p2), set_one(p3);
            join(t, p3, t), join(t, p2, t), join(t, p1, t);
        }
        cout << max({t->mx, t->zp, t->zs, t->op, t->os}) << '\n';
    }
}