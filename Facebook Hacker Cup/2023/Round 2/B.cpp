#include <bits/stdc++.h>

using namespace std;

template <int base, int... prime_list>
struct KarpRabin {
    static constexpr int num_hashes = sizeof...(prime_list);
    static constexpr array<int, num_hashes> primes = array<int, num_hashes>{forward<int>(prime_list)...};
    static inline vector<array<int, num_hashes>> exp;
    array<int, num_hashes> hsh;
    KarpRabin() {hsh.fill(0);}
    KarpRabin(int a) {hsh.fill(a + 1);}
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
using kr_hash = KarpRabin<1000000002, 1000000007>; // add in as many primes as you want :)

int main() {
    ifstream cin("meta_game_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        deque<int> a(n), b(n), tot;
        for(int i = 0; i < n; i++) {
            cin >> a[i]; tot.push_back(a[i]);
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i]; tot.push_back(b[i]);
        }
        vector<kr_hash> pf(1), rpf(1);
        for(int i = 0; i < 2 * n; i++) {
            pf.push_back((pf.back() << 1) + kr_hash(tot[i]));
            rpf.push_back((rpf.back() << 1) + kr_hash(tot[2 * n - i - 1]));
        }
        vector<bool> c1(2 * n, false), c2(2 * n, false);
        for(int i = 0; i < 2 * n; i++) { // reverse check
            kr_hash f1 = pf[i];
            kr_hash f2 = (pf[2 * n] - (pf[i] << (2 * n - i)));
            kr_hash fw = (f2 << i) + f1;
            kr_hash b1 = (rpf[2 * n] - (rpf[2 * n - i] << i));
            kr_hash b2 = rpf[2 * n - i];
            kr_hash bw = (b1 << (2 * n - i)) + b2;
            c1[i] = fw == bw;
        }
        int t1 = 0, st = 0;
        for(int i = 0; i < n; i++) {
            t1 += (a[i] < b[i]);
        }
        for(int i = n - 1; i >= 0; i--) {
            if(a[i] <= b[i]) break;
            ++st;
        }
        for(int i = 0; i < 2 * n; i++) { // streak check
            int yo = t1;
            if(n % 2 == 1 && a[n / 2] < b[n / 2]) --yo;
            c2[i] = (st >= n / 2 && yo == n / 2);
            a.push_back(b.front()); b.push_back(a.front());
            if(a[0] < b[0]) --t1;
            if(a.back() > b.back()) {
                ++st;
            } else {
                st = 0;
                if(a.back() < b.back()) ++t1;
            }
            a.pop_front(); b.pop_front();
        }
        int ans = -1;
        for(int i = 0; i < 2 * n; i++) {
            if(c1[i] && c2[i]) {
                ans = i;
                break;
            }
        }
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}