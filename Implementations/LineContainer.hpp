struct Line {
    ll m, b;
    mutable ll ep;
    bool operator<(const Line & l) const {
        return m < l.m;
    }
    bool operator<(ll x) const {
        return ep < x;
    }
};

struct LineContainer : multiset<Line, less<>> { // defaults to max
    static const ll INF = LLONG_MAX;
    ll div(ll x, ll y) {
        return x / y - ((x ^ y) < 0 && x % y);
    }
    bool upd(iterator x, iterator y) {
        if(y == end()) {
            x->ep = INF;
            return false;
        }
        if(x->m == y->m) x->ep = (x->b < y->b ? -INF : INF);
        else x->ep = div(x->b - y->b, y->m - x->m);
        return x->ep >= y->ep;
    }
    void add(ll m, ll b) {
        auto z = insert({m, b, 0}), y = z++, x = y;
        while(upd(y, z)) z = erase(z);
        if(x != begin() && upd(--x, y)) upd(x, y = erase(y));
        while((y = x) != begin() && (--x)->ep >= y->ep) upd(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto it = *lower_bound(x);
        return it.m * x + it.b;
    }
};