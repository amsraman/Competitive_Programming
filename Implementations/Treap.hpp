mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <class B> struct Treap {
    using T_k = typename B::T_k;
    using T_v = typename B::T_v;
    T_k key; T_v val, aug; int pr, size;
    Treap *l, *r;
    inline int rand_int() {return uniform_int_distribution<int>(INT_MIN, INT_MAX)(rng);}
    Treap(T_v val): val(val), aug(val), pr(rand_int()), size(1), l(NULL), r(NULL) {};
    friend void refresh(Treap *t) {
        if(t) {
            t->size = 1 + (t->l ? t->l->size : 0) + (t->r ? t->r->size : 0);
            t->aug = B::comb(B::comb(t->l ? t->l->aug : B::e, t->val), t->r ? t->r->aug : B::e);
        }
    }
    friend pair<Treap*, Treap*> split_by_order(Treap *t, int sz) {
        if(!t) return {NULL, NULL};
        int left_sz = (t->l ? t->l->size : 0);
        if(left_sz < sz) {
            auto [lp, rp] = split_by_order(t->r, sz - left_sz - 1);
            t->r = lp; refresh(t);
            return {t, rp};
        } else {
            auto [lp, rp] = split_by_order(t->l, sz);
            t->l = rp; refresh(t);
            return {lp, t};
        }
    }
    friend Treap* join(Treap *l, Treap *r) {
        if(!l || !r) return (l ?: r);
        if(l->pr >= r->pr) {
            l->r = join(l->r, r); refresh(l);
            return l;
        } else {
            r->l = join(l, r->l); refresh(r);
            return r;
        }
    }
};

// Sample Monoid

struct Monoid {
    using T_k = monostate;
    using T_v = long long;
    static const T_v e = 0;
    static T_v comb(T_v a, T_v b) {
        return a + b;
    }
};