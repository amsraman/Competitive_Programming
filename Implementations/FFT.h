typedef complex<double> cd;

const double PI = acos(-1);

void fft(vector<cd> & a, bool inv) {
    int sz = a.size();
    for(int i = 1, j = 0; i < sz; i++) {
        int bit = sz >> 1;
        for(; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if(i < j) {
            swap(a[i], a[j]);
        }
    }
    for(int len = 1; len < sz; len <<= 1) {
        double ang = PI / len * (inv ? 1 : -1);
        cd w(cos(ang), sin(ang));
        for(int i = 0; i < sz; i += (2 * len)) {
            cd wn(1);
            for(int j = i; j < i + len; j++) {
                cd x = a[j], y = a[j + len] * wn;
                a[j] = x + y;
                a[j + len] = x - y;
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

void fft_conv(vector<cd> & a, vector<cd> & b) {
    // convolves a and b into a
    int pow = 1, res_sz = a.size() + b.size() - 1;
    while(pow < res_sz) {
        pow <<= 1;
    }
    a.resize(pow), b.resize(pow);
    fft(a, false), fft(b, false);
    for(int i = 0; i < pow; i++) {
        a[i] *= b[i];
    }
    fft(a, true);
    for(int i = 0; i < pow; i++) {
        a[i] = (long long) round(a[i].real()) % mod;
    }
}