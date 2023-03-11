// 1047 ms
#include <bits/stdc++.h>

using namespace std;

template <class B>
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
    PowerSeries operator*(const PowerSeries & p) const { // O(N log N)
        PowerSeries res(*this);
        B::convolve(res.poly, p.poly);
        return res;
    }
    friend PowerSeries shorten(const PowerSeries & p, size_t n) {
        n = min(n, p.poly.size());
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
        PowerSeries two(1, 2), res(1, B::exp(p.poly[0], B::mod - 2));
        for(int i = 1; i < n; i <<= 1) {
            res = res * (two - (shorten(p, i << 1) * res));
            res.poly.resize(i << 1);
        }
        res.poly.resize(n);
        return res;
    }
    friend PowerSeries log(PowerSeries & p, size_t n) { // O(N log N)
        assert(p.poly[0] == 1);
        PowerSeries res = integr(deriv(p) * inv(p, n));
        res.poly.resize(n);
        return res;
    }
    friend PowerSeries exp(PowerSeries & p, size_t n) {};
    friend PowerSeries pow(PowerSeries & p, T num, size_t n) {};
    T eval(T x) {};
    vector<T> eval(vector<T> & x) {};
};

struct NTT {
    using T = int;
    static const int mod = 998244353, generator = 3;
    static T mul(T a, T b) {
        return (1LL * a * b) % mod;
    }
    static T exp(T a, T b) {
        T ret = 1;
        while(b > 0) {
            if(b & 1) {
                ret = mul(ret, a);
            }
            a = mul(a, a), b >>= 1;
        }
        return ret;
    }
    static void ntt(vector<T> & a, bool inv) {
        int sz = a.size();
        assert((mod - 1) % a.size() == 0);
        for(int i = 1, j = 0; i < sz; i++) {
            int bit = sz >> 1;
            for(; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if(i < j) swap(a[i], a[j]);
        }
        for(int len = 1; len < sz; len <<= 1) {
            T w = exp(3, mod / 2 / len);
            if(inv) w = exp(w, mod - 2);
            for(int i = 0; i < sz; i += (2 * len)) {
                T wn = 1;
                for(int j = i; j < i + len; j++) {
                    T x = a[j], y = mul(a[j + len], wn);
                    a[j] = (x + y) % mod;
                    a[j + len] = (x - y + mod) % mod;
                    wn = mul(wn, w);
                }
            }
        }
        if(inv) {
            T inv_n = exp(sz, mod - 2);
            for(int i = 0; i < sz; i++) {
                a[i] = mul(a[i], inv_n);
            }
        }
    }
    static void convolve(vector<T> & a, vector<T> b) { // onto a
        int pow = 1, res_sz = a.size() + b.size() - 1;
        while(pow < res_sz) pow <<= 1;
        a.resize(pow), b.resize(pow);
        ntt(a, false), ntt(b, false);
        for(int i = 0; i < pow; i++) {
            a[i] = mul(a[i], b[i]);
        }
        ntt(a, true), a.resize(res_sz);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    PowerSeries<NTT> p(n);
    for(int i = 0; i < n; i++) {
        cin >> p.poly[i];
    }
    auto res = log(p, n);
    for(auto val: res.poly) {
        cout << val << " ";
    }
    cout << '\n';
}