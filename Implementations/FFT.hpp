struct FFT {
    using cd = complex<double>;
    static constexpr double PI = acos(-1);
    static void fft(vector<cd> & a, bool inv) {
        int sz = a.size();
        for(int i = 1, j = 0; i < sz; i++) {
            int bit = sz >> 1;
            for(; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if(i < j) swap(a[i], a[j]);
        }
        for(int len = 1; len < sz; len <<= 1) {
            double ang = PI / len * (inv ? 1 : -1);
            cd w(cos(ang), sin(ang));
            for(int i = 0; i < sz; i += (2 * len)) {
                cd wn(1);
                for(int j = i; j < i + len; j++) {
                    cd x = a[j], y = a[j + len] * wn;
                    a[j] = x + y, a[j + len] = x - y;
                    wn *= w;
                }
            }
        }
        if(inv) {
            for(int i = 0; i < sz; i++) {
                a[i] /= sz;
            }
        }
    }
    template <typename T>
    static void convolve(vector<T> & a, vector<T> & b) { // onto a
        vector<cd> ca(a.begin(), a.end()), cb(b.begin(), b.end());
        int pow = 1, res_sz = a.size() + b.size() - 1;
        while(pow < res_sz) {
            pow <<= 1;
        }
        ca.resize(pow), cb.resize(pow);
        fft(ca, false), fft(cb, false);
        for(int i = 0; i < pow; i++) {
            ca[i] *= cb[i];
        }
        fft(ca, true);
        a.resize(res_sz);
        for(int i = 0; i < res_sz; i++) {
            a[i] = round(ca[i].real());
        }
    }
};