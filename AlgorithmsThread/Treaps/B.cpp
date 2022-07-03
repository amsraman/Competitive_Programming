#include <bits/stdc++.h>

using namespace std;

const int mod1 = 1e9 + 7, mod2 = (117 << 23) + 1;

int p1[600001], p2[600001];

struct Node {
    char key;
    int priority, sz, h1, h2;
    Node *l, *r;
    Node(char key): key(key), priority(rand()), sz(1), h1(key), h2(key), l(NULL), r(NULL) {};
    Node(char key, int priority): key(key), priority(priority), sz(1), h1(key), h2(key), l(NULL), r(NULL) {};
};
typedef Node* Treap;

void refresh(Treap t) {
    if(t) {
        int left_sz = (t->l ? t->l->sz : 0), right_sz = (t->r ? t->r->sz : 0);
        int left_h1 = (t->l ? t->l->h1 : 0), right_h1 = (t->r ? t->r->h1 : 0);
        int left_h2 = (t->l ? t->l->h2 : 0), right_h2 = (t->r ? t->r->h2 : 0);
        t->sz = 1 + left_sz + right_sz;
        t->h1 = ((1LL * p1[right_sz + 1] * left_h1) % mod2 + 1LL * t->key * p1[right_sz] + right_h1) % mod2;
        t->h2 = ((1LL * p2[right_sz + 1] * left_h2) % mod1 + 1LL * t->key * p2[right_sz] + right_h2) % mod1;
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

void insert(Treap & t, Treap new_node, int pos) {
    if(!t) {
        t = new_node;
    } else if(new_node->priority > t->priority) {
        split(t, pos, new_node->l, new_node->r), t = new_node;
    } else if((t->l ? t->l->sz : 0) + 1 <= pos) {
        insert(t->r, new_node, pos - (t->l ? t->l->sz : 0) - 1);
    } else {
        insert(t->l, new_node, pos);
    }
    refresh(t);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    string s;
    cin >> n >> q >> s;
    p1[0] = p2[0] = 1;
    for(int i = 1; i <= n + q; i++) {
        p1[i] = (1LL * p1[i - 1] * mod1) % mod2;
        p2[i] = (1LL * p2[i - 1] * mod2) % mod1;
    }
    Treap tf = NULL, tr = NULL;
    for(int i = 0; i < n; i++) {
        insert(tf, new Node(s[i]), i);
        insert(tr, new Node(s[n - i - 1]), i);
    }
    while(q--) {
        int t, x, y, p;
        char c;
        cin >> t;
        if(t == 1) {
            cin >> x >> y;
            Treap first_part, middle_part;
            split(tf, x - 1, first_part, tf);
            split(tf, y - x + 1, middle_part, tf);
            join(tf, first_part, tf);
            split(tr, n - y, first_part, tr);
            split(tr, y - x + 1, middle_part, tr);
            join(tr, first_part, tr);
            n -= y - x + 1;
        } else if(t == 2) {
            cin >> c >> p;
            insert(tf, new Node(c), p - 1);
            insert(tr, new Node(c), n - p + 1);
            ++n;
        } else {
            cin >> x >> y;
            Treap fp1, mp1, fp2, mp2;
            split(tf, x - 1, fp1, tf);
            split(tf, y - x + 1, mp1, tf);
            split(tr, n - y, fp2, tr);
            split(tr, y - x + 1, mp2, tr);
            cout << ((mp1->h1 == mp2->h1 && mp1->h2 == mp2->h2) ? "yes" : "no") << '\n';
            join(tf, mp1, tf), join(tf, fp1, tf);
            join(tr, mp2, tr), join(tr, fp2, tr);
        }
    }
}