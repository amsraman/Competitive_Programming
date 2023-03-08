#include <bits/stdc++.h>
typedef __int128_t ll;

using namespace std;

template <typename T>
struct frac {
    T num, den;
    frac(): num(0), den(1) {};
    frac(T c): num(c), den(1) {};
    frac(T n, T d): num(n), den(d) {
        T g = __gcd(num, den);
        num /= g, den /= g;
        if(den < 0) {
            num *= -1, den *= -1;
        }
    };
    bool operator==(T cons) {return (cons * this->den == this->num);}
    bool operator!=(T cons) {return (cons * this->den != this->num);}
    bool operator<(T cons) {return (this->num < cons * this->den);}
    bool operator>(T cons) {return (this->num > cons * this->den);}
    frac operator+(const frac & f) const {
        T g = __gcd(this->den, f.den), lcm = this->den / g * f.den;
        return frac(this->num * (f.den / g) + f.num * (this->den / g), lcm);
    }
    frac operator-(const frac & f) const {
        T g = __gcd(this->den, f.den), lcm = this->den / g * f.den;
        return frac(this->num * (f.den / g) - f.num * (this->den / g), lcm);
    }
    frac operator*(T coef) {
        T g = __gcd(coef, this->den);
        return frac(this->num * (coef / g), this->den / g);
    }
    frac operator*(const frac & f) const {
        T g1 = __gcd(this->num, f.den), g2 = __gcd(this->den, f.num);
        return frac((this->num / g1) * (f.num / g2), (this->den / g2) * (f.den / g1));
    }
    frac operator/(T coef) {
        T g = __gcd(coef, this->num);
        return frac(this->num / g, this->den * (coef / g));
    }
    frac operator/(const frac & f) const {
        T g1 = __gcd(this->num, f.num), g2 = __gcd(this->den, f.den);
        return frac((this->num / g1) * (f.den / g2), (this->den / g2) * (f.num / g1));
    }
    void operator+=(const frac & f) {*this = *this + f;}
    void operator-=(const frac & f) {*this = *this - f;}
    void operator*=(T coef) {*this = *this * coef;}
    void operator*=(const frac & f) {*this = *this * f;}
    void operator/=(T coef) {*this = *this / coef;}
    void operator/=(const frac & f) {*this = *this / f;}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n1, n2; cin >> n1 >> n2;
    for(int _ = 1; n1 != 0 || n2 != 0; _++) {
        vector<int> rat1(n1), rat2(n2);
        for(int i = 0; i < n1; i++) cin >> rat1[i];
        for(int i = 0; i < n2; i++) cin >> rat2[i];
        frac<ll> r1 = rat1[n1 - 1], r2 = rat2[n2 - 1];
        for(int i = n1 - 2; i >= 0; i--) r1 = frac<ll>(rat1[i]) + frac<ll>(1) / r1;
        for(int i = n2 - 2; i >= 0; i--) r2 = frac<ll>(rat2[i]) + frac<ll>(1) / r2;
        frac<ll> ans1 = r1 + r2, ans2 = r1 - r2, ans3 = r1 * r2, ans4 = r1 / r2;
        auto print_cont = [](frac<ll> f) {
            if(f == 0) {
                cout << "0\n";
                return;
            }
            while(true) {
                long long cur = f.num / f.den;
                if(f.num < 0) {
                    cur = (f.num - f.den + 1) / f.den;
                }
                cout << cur << " ";
                if(f == cur) break;
                f = frac<ll>(1) / (f - cur);
            }
            cout << '\n';
        };
        cout << "Case " << _ << ": ";
        print_cont(ans1);
        print_cont(ans2);
        print_cont(ans3);
        print_cont(ans4);
        cin >> n1 >> n2;
    }
}