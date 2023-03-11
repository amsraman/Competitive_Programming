template <class B> // Convolver
struct PowerSeries {
    using T = typename B::T;
    vector<T> poly;
    PowerSeries(size_t size, T init = 0): poly(size, init) {};
    PowerSeries(const vector<T> & init): poly(init) {};
    inline size_t size() const {return poly.size();}
    inline T val(size_t n) const {return (n >= poly.size() ? 0 : poly[n]);}
    PowerSeries operator+(const PowerSeries & p) const { // O(N)
        size_t res_sz = max(this->size(), p.size());
        PowerSeries res(res_sz);
        for(int i = 0; i < res_sz; i++) {
            res.poly[i] = (this->val(i) + p.val(i)) % B::mod;
        }
        return res;
    }
    PowerSeries operator-(const PowerSeries & p) const { // O(N)
        size_t res_sz = max(this->size(), p.size());
        PowerSeries res(res_sz);
        for(int i = 0; i < res_sz; i++) {
            res.poly[i] = (this->val(i) - p.val(i) + B::mod) % B::mod;
        }
        return res;
    }
    PowerSeries operator*(T c) const {
        PowerSeries res(*this);
        for(int i = 0; i < res.size(); i++) res.poly[i] = B::mul(res.poly[i], c);
        return res;
    }
    PowerSeries operator*(const PowerSeries & p) const { // O(N log N)
        PowerSeries res(*this);
        B::convolve(res.poly, p.poly);
        return res;
    }
    friend PowerSeries shorten(const PowerSeries & p, size_t n) {
        n = min(n, p.size());
        PowerSeries res(n); copy(p.poly.begin(), p.poly.begin() + n, res.poly.begin());
        return res;
    }
    friend PowerSeries deriv(const PowerSeries & p) { // O(N)
        assert(!p.poly.empty());
        PowerSeries res((int) p.size(), 0);
        for(int i = 0; i + 1 < (int) p.size(); i++) res.poly[i] = B::mul(i + 1, p.poly[i + 1]);
        if(res.size() > 1) res.poly.pop_back();
        return res;
    }
    friend PowerSeries integr(const PowerSeries & p) { // O(N)
        PowerSeries res((int) p.size() + 1, 0);
        for(int i = 0; i < (int) p.size(); i++) {
            res.poly[i + 1] = B::mul(B::exp(i + 1, B::mod - 2), p.poly[i]);
        }
        return res;
    }
    friend PowerSeries inv(const PowerSeries & p, size_t n) { // O(N log N)
        assert(p.poly[0] != 0);
        PowerSeries two(1, 2), res(1, B::exp(p.poly[0], B::mod - 2));
        for(int i = 1; i < n; i <<= 1) {
            res = res * (two - (shorten(p, i << 1) * res));
            res.poly.resize(i << 1);
        }
        res.poly.resize(n);
        return res;
    }
    friend pair<PowerSeries, PowerSeries> divmod(const PowerSeries & a, const PowerSeries & b) { // O(N log N)
        int n = a.size(), m = b.size();
        if(n < m) return {PowerSeries(0), a};
        PowerSeries ra({a.poly.rbegin(), a.poly.rend()}), rb({b.poly.rbegin(), b.poly.rend()});
        PowerSeries rq = shorten(ra * inv(rb, n - m + 1), n - m + 1);
        PowerSeries q({rq.poly.rbegin(), rq.poly.rend()}), r = a - q * b;
        while(!r.poly.empty() && r.poly.back() == 0) r.poly.pop_back();
        return {q, r};
    }
    PowerSeries operator/(const PowerSeries & p) {
        auto [q, _] = divmod(*this, p);
        return q;
    }
    PowerSeries operator%(const PowerSeries & p) {
        auto [_, r] = divmod(*this, p);
        return r;
    }
    friend PowerSeries log(PowerSeries & p, size_t n) { // O(N log N)
        assert(p.poly[0] == 1);
        PowerSeries res = integr(deriv(p) * inv(p, n));
        res.poly.resize(n);
        return res;
    }
    friend PowerSeries exp(const PowerSeries & p, size_t n) { // O(N log N)
        PowerSeries one(1, 1), res(1, 1);
        for(int i = 1; i < n; i <<= 1) {
            res = res * (one + shorten(p, i << 1) - log(res, i << 1));
            res.poly.resize(i << 1);
        }
        res.poly.resize(n);
        return res;
    }
    friend PowerSeries pow(PowerSeries & p, long long num, size_t n) {
        if(num == 0) {
            PowerSeries res(n); res.poly[0] = 1;
            return res;
        }
        PowerSeries init(p.poly);
        int offset = 0; T lval;
        while(offset < (int) init.size() && init.poly[offset] == 0) ++offset;
        if(offset == (int) init.size()) {
            return PowerSeries(n);
        }
        init.poly.erase(init.poly.begin(), init.poly.begin() + offset); lval = init.poly[0];
        init = init * B::exp(lval, B::mod - 2);
        if(offset > 0) offset = min((long long int) n, min(num, LLONG_MAX / offset) * offset);
        PowerSeries res = exp(log(init, n) * (num % B::mod), n) * B::exp(lval, num % (B::mod - 1));
        res.poly.insert(res.poly.begin(), offset, 0);
        return shorten(res, n);
    };
    friend PowerSeries taylor_shift(const PowerSeries & p, T c) { // O(N log N)
        int n = p.size();
        vector<T> fact(n, 1), ifact(n), v1(n, p.poly[0]), v2(n, 1);
        for(int i = 1; i < n; i++) {
            fact[i] = B::mul(fact[i - 1], i);
            v1[i] = B::mul(fact[i], p.poly[i]);
            v2[n - i - 1] = B::mul(v2[n - i], c);
        };
        ifact[n - 1] = B::exp(fact[n - 1], B::mod - 2);
        for(int i = n - 1; i >= 0; i--) {
            if(i < n - 1) ifact[i] = B::mul(ifact[i + 1], i + 1);
            v2[n - i - 1] = B::mul(v2[n - i - 1], ifact[i]);
        }
        B::convolve(v1, v2);
        PowerSeries res(n);
        for(int i = 0; i < n; i++) res.poly[i] = B::mul(v1[i + n - 1], ifact[i]);
        return res;
    }
    static vector<PowerSeries> monomial_tree(const vector<T> & x) {
        int n = x.size(), sz = 1 << (__lg(n) + 1);
        vector<PowerSeries> mt(2 * sz, PowerSeries(1, 1));
        for(int i = 0; i < n; i++) mt[i + sz] = PowerSeries(vector<T>{B::mod - x[i], 1});
        for(int i = sz - 1; i > 0; i--) mt[i] = mt[2 * i] * mt[2 * i + 1];
        return mt;
    }
    static void multipoint_eval(const vector<PowerSeries> & mt, PowerSeries cur, vector<T> & res, int lo, int hi, int ind) {
        if(lo == hi) {
            if(lo < (int) res.size()) res[lo] = cur.val(0);
            return;
        }
        int mid = (lo + hi) / 2;
        multipoint_eval(mt, cur % mt[2 * ind], res, lo, mid, 2 * ind);
        multipoint_eval(mt, cur % mt[2 * ind + 1], res, mid + 1, hi, 2 * ind + 1);
    }
    T eval(T x) { // O(N)
        T res = 0;
        for(int i = (int) poly.size() - 1; i >= 0; i--) {
            res = (B::mul(res, x) + poly[i]) % B::mod;
        }
        return res;
    }
    vector<T> eval(const vector<T> & x) { // O(N log^2 N)
        int m = x.size(), sz = (1 << (__lg(m) + 1));
        vector<T> res;
        multipoint_eval(monomial_tree(x), *this, x, res, 0, sz - 1, 1);
        return res;
    }
    static PowerSeries interpolate(const vector<T> & x, const vector<T> & y) { // O(N log^2 N)
        assert(x.size() == y.size());
        int n = x.size(), sz = 1 << (__lg(n) + 1);
        vector<PowerSeries> mt = monomial_tree(x);
        vector<T> p(n);
        multipoint_eval(mt, deriv(mt[1]), p, 0, sz - 1, 1);
        auto interp = [&](auto rec, int lo, int hi, int ind) -> PowerSeries {
            if(lo == hi) {
                T val = (lo < n ? B::mul(y[lo], B::exp(p[lo], B::mod - 2)) : 0);
                return PowerSeries(1, val);
            }
            int mid = (lo + hi) / 2;
            return rec(rec, lo, mid, 2 * ind) * mt[2 * ind + 1] + rec(rec, mid + 1, hi, 2 * ind + 1) * mt[2 * ind];
        };
        PowerSeries res = interp(interp, 0, sz - 1, 1); res.poly.pop_back();
        return res;
    }
};