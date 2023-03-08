template <int base, int... prime_list>
struct KarpRabin {
    static constexpr int num_hashes = sizeof...(prime_list);
    static constexpr array<int, num_hashes> primes = array<int, num_hashes>{forward<int>(prime_list)...};
    static inline vector<array<int, num_hashes>> exp;
    array<int, num_hashes> hsh;
    KarpRabin() {hsh.fill(0);}
    KarpRabin(char c) {hsh.fill(ctoi(c));}
    inline int ctoi(char c) const {
        int tp = (c == '.' ? 0 : c - 'a' + 1);
        return tp * tp * tp;
    }
    inline void extend_pow(int num) {
        if(exp.empty()) {
            array<int, num_hashes> init; init.fill(1); exp.push_back(init);
        }
        while((int) exp.size() <= num) {
            array<int, num_hashes> nxt = exp.back();
            for(int i = 0; i < num_hashes; i++) nxt[i] = (1LL * nxt[i] * base) % primes[i];
            exp.push_back(nxt);
        }
    }
    KarpRabin operator+(const KarpRabin & h) const {
        KarpRabin res;
        for(int i = 0; i < num_hashes; i++) res.hsh[i] = (this->hsh[i] + h.hsh[i]) % primes[i];
        return res;
    }
    KarpRabin operator-(const KarpRabin & h) const {
        KarpRabin res;
        for(int i = 0; i < num_hashes; i++) res.hsh[i] = (this->hsh[i] - h.hsh[i] + primes[i]) % primes[i];
        return res;
    }
    KarpRabin operator+(const char c) const {return *this + KarpRabin(c);}
    KarpRabin operator<<(int num) {
        KarpRabin res; array<int, num_hashes> pw;
        extend_pow(num); pw = exp[num];
        for(int i = 0; i < num_hashes; i++) res.hsh[i] = (1LL * this->hsh[i] * pw[i]) % primes[i];
        return res;
    }
    bool operator==(const KarpRabin & h) const {return this->hsh == h.hsh;}
    size_t operator()(const KarpRabin & h) const {return hsh[0];}
};
using kr_hash = KarpRabin<10000, 1000000007, 998244353>; // add in as many primes as you want :)