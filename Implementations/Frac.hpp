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
    bool operator==(T cons) {
        return (cons * this->den == this->num);
    }
    bool operator!=(T cons) {
        return (cons * this->den != this->num);
    }
    bool operator<(T cons) {
        return (this->num < cons * this->den);
    }
    bool operator>(T cons) {
        return (this->num > cons * this->den);
    }
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
    void operator+=(const frac & f) {
        *this = *this + f;
    }
    void operator-=(const frac & f) {
        *this = *this - f;
    }
    void operator*=(T coef) {
        *this = *this * coef;
    }
    void operator*=(const frac & f) {
        *this = *this * f;
    }
    void operator/=(T coef) {
        *this = *this / coef;
    }
    void operator/=(const frac & f) {
        *this = *this / f;
    }
};