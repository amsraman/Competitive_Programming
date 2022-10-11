// This is ok but I need to make it better
template <typename T>
struct Node {
    T key;
    int priority, sz;
    Node *l, *r;
    Node(T key): key(key), priority(rand()), sz(1), l(NULL), r(NULL) {};
    Node(T key, int priority): key(key), priority(priority), sz(1), l(NULL), r(NULL) {};
    void refresh(Treap t) {
        if(t) {
            t->sz = 1 + (t->l ? t->l->sz : 0) + (t->r ? t->r->sz : 0);
        }
    }
    friend void split_by_key(Treap t, int key, Treap & l, Treap & r) {
        if(!t) {
            l = r = NULL;
        } else if(t->key <= key) {
            split_by_key(t->r, key, t->r, r), l = t;
        } else {
            split_by_key(t->l, key, l, t->l), r = t;
        }
        refresh(t);
    }
    friend void split_by_order(Treap t, int num, Treap & l, Treap & r) {
        if(!t) {
            l = r = NULL;
        } else if((t->l ? t->l->sz : 0) + 1 <= num) {
            split_by_order(t->r, num - (t->l ? t->l->sz : 0) - 1, t->r, r), l = t;
        } else {
            split_by_order(t->l, num, l, t->l), r = t;
        }
        refresh(t);
    }
    friend void join(Treap & t, Treap l, Treap r) {
        if(!l || !r) {
            t = l ? l : r;
        } else if(l->priority > r->priority) {
            join(l->r, l->r, r), t = l;
        } else {
            join(r->l, l, r->l), t = r;
        }
        refresh(t);
    }
    friend void insert(Treap & t, Treap new_node) {
        if(!t) {
            t = new_node;
        } else if(new_node->priority > t->priority) {
            split_by_key(t, new_node->key, new_node->l, new_node->r), t = new_node;
        } else {
            insert(t->key <= new_node->key ? t->r : t->l, new_node);
        }
        refresh(t);
    }
};
typedef Node<int>* Treap;