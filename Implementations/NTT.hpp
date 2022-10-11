namespace NTT {
    const int mod = 998244353;

    int mul(int a, int b) {
        return (1LL * a * b) % mod;
    }
    
    int exp(int a, int b) {
        int ret = 1;
        while(b > 0) {
            if(b & 1) {
                ret = mul(ret, a);
            }
            a = mul(a, a), b >>= 1;
        }
        return ret;
    }

    void ntt(vector<int> & a, bool inv) {
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
            int w = exp(3, mod / 2 / len);
            if(inv) {
                w = exp(w, mod - 2);
            }
            for(int i = 0; i < sz; i += (2 * len)) {
                int wn = 1;
                for(int j = i; j < i + len; j++) {
                    int x = a[j], y = mul(a[j + len], wn);
                    a[j] = (x + y) % mod;
                    a[j + len] = (x - y + mod) % mod;
                    wn = mul(wn, w);
                }
            }
        }
        if(inv) {
            int inv_n = exp(sz, mod - 2);
            for(int i = 0; i < sz; i++) {
                a[i] = mul(a[i], inv_n);
            }
        }
    }

    void ntt_conv(vector<int> & a, vector<int> & b) {
        int pow = 1, res_sz = a.size() + b.size() - 1;
        while(pow < res_sz) {
            pow <<= 1;
        }
        a.resize(pow), b.resize(pow);
        ntt(a, false), ntt(b, false);
        for(int i = 0; i < pow; i++) {
            a[i] = mul(a[i], b[i]);
        }
        ntt(a, true);
    }
}