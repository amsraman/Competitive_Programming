#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key, priority, sz;
    Node *l, *r;
    Node(int key): key(key), priority(rand()), sz(1), l(NULL), r(NULL) {};
    Node(int key, int priority): key(key), priority(priority), sz(1), l(NULL), r(NULL) {};
};
typedef Node* Treap;

void refresh(Treap t) {
    if(t) {
        t->sz = 1 + (t->l ? t->l->sz : 0) + (t->r ? t->r->sz : 0);
    }
}

void split_by_key(Treap t, int key, Treap & l, Treap & r) {
    if(!t) {
        l = r = NULL;
    } else if(t->key <= key) {
        split_by_key(t->r, key, t->r, r), l = t;
    } else {
        split_by_key(t->l, key, l, t->l), r = t;
    }
    refresh(t);
}

void split_by_size(Treap t, int num, Treap & l, Treap & r) {
    if(!t) {
        l = r = NULL;
    } else if((t->l ? t->l->sz : 0) + 1 <= num) {
        split_by_size(t->r, num - (t->l ? t->l->sz : 0) - 1, t->r, r), l = t;
    } else {
        split_by_size(t->l, num, l, t->l), r = t;
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

void insert(Treap & t, Treap new_node) {
    if(!t) {
        t = new_node;
    } else if(new_node->priority > t->priority) {
        split_by_key(t, new_node->key, new_node->l, new_node->r), t = new_node;
    } else {
        insert(t->key <= new_node->key ? t->r : t->l, new_node);
    }
    refresh(t);
}

void traverse(Treap t) {
    if(!t) {
        return;
    }
    traverse(t->l);
    cout << t->key << " ";
    traverse(t->r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    Treap t = NULL;
    for(int i = 1; i <= n; i++) {
        insert(t, new Node(i));
    }
    for(int i = 0, a, b; i < n; i++) {
        cin >> a >> b;
        if(a > b) {
            continue;
        }
        int sz = min(b - a, n - b + 1);
        Treap t1, t2, t3, t4;
        split_by_size(t, a - 1, t1, t);
        split_by_size(t, sz, t2, t);
        split_by_size(t, b - a - sz, t3, t);
        split_by_size(t, sz, t4, t);
        join(t, t2, t);
        join(t, t3, t);
        join(t, t4, t);
        join(t, t1, t);
    }
    traverse(t);
    cout << '\n';
}