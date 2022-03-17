#include <bits/stdc++.h>
typedef __int128_t ll;

using namespace std;

int m, n, p;
ll fact[51];

void pr_128(ll num) {
    if(num == 0) {
        cout << 0;
        return;
    }
    vector<int> dig;
    while(num > 0) {
        dig.push_back(num % 10);
        num /= 10;
    }
    reverse(dig.begin(), dig.end());
    for(int d: dig) {
        cout << d;
    }
}

struct frac {
    ll num, den;

    frac(): num(0), den(1) {};

    frac(ll n, ll d): num(n), den(d) {
        ll g = __gcd(num, den);
        num /= g, den /= g;
    };

    frac operator+(const frac &f) const {
        ll g = __gcd(this->den, f.den), lcm = this->den / g * f.den;
        return frac(this->num * (f.den / g) + f.num * (this->den / g), lcm);
    }

    frac operator-(const frac &f) const {
        ll g = __gcd(this->den, f.den), lcm = this->den / g * f.den;
        return frac(this->num * (f.den / g) - f.num * (this->den / g), lcm);
    }

    frac operator*(ll coef) {
        ll g = __gcd(coef, this->den);
        return frac(this->num * (coef / g), this->den / g);
    }

    frac operator*(const frac &f) const {
        ll g1 = __gcd(this->num, f.den), g2 = __gcd(this->den, f.num);
        return frac((this->num / g1) * (f.num / g2), (this->den / g2, f.den / g1));
    }

    void operator+=(const frac &f) {
        *this = *this + f;
    }

    void operator-=(const frac &f) {
        *this = *this - f;
    }

    void operator*=(ll coef) {
        *this = *this * coef;
    }

    void operator*=(const frac &f) {
        *this = *this * f;
    }

    void pr() {
        pr_128(num);
        cout << '/';
        pr_128(den);
        cout << '\n';
    }
};

ll choose(int n, int r) {
    if(n < r || r < 0) {
        return 0;
    }
    return fact[n] / fact[n - r] / fact[r];
}

frac get_ans(int p) {
    if(p < 0) {
        return frac(0, 1);
    }
    frac ret(0, 1);
    for(int i = 1; i <= n; i++) {
        frac num;
        if(m - p - 2 * i >= 0) {
            num = frac(fact[m - 2 * i], fact[m - p - 2 * i]);
            num *= frac(fact[m - p], fact[m]);
        }
        num *= choose(n, i);
        if(i & 1) {
            ret += num;
        } else {
            ret -= num;
        }
    }
    return frac(1, 1) - ret;
}

int main() {
    cin >> m >> n >> p;
    fact[0] = 1;
    for(int i = 1; i <= 50; i++) {
        fact[i] = i * fact[i - 1];
    }
    (get_ans(p) - get_ans(p - 1)).pr();
}