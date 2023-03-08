#include <bits/stdc++.h>

using namespace std;

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
using kr_hash = KarpRabin<10000, 998244353>;

struct PieceHasher {
    int n, m, pad, padded_len, ind, lp = 0;
    vector<kr_hash> pf; kr_hash hsh;
    PieceHasher() {};
    PieceHasher(const vector<string> & s, int pad, int ind = -1): n((int) s.size()), m((int) s[0].length()), pad(pad), ind(ind), pf(n * m + 1) {
        padded_len = n * m + (n - 1) * pad;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                pf[i * m + j + 1] = (pf[i * m + j] << (1 + pad * (j == 0))) + s[i][j];
                if(s[i][j] != '.') lp = (n - i - 1) * (m + pad) + m - j;
            }
        }
        hsh = pf[n * m];
    }
    kr_hash suffix(int i) {
        if(i == padded_len) return pf[n * m];
        i = padded_len - i - 1;
        i = i / (m + pad) * m + min(m - 1, i % (m + pad));
        i = n * m - i - 1;
        return pf[n * m] - (pf[n * m - i] << (i + i / m * pad));
    }
};

int main() {
    ifstream cin("bcs.in");
    ofstream cout("bcs.out");
    // String Helper Functions
    auto read_piece = [&](int r, int c) {
        vector<string> piece(r);
        int mnr = r, mxr = 0, mnc = c, mxc = 0;
        for(int i = 0; i < r; i++) {
            cin >> piece[i];
            for(int j = 0; j < c; j++) {
                if(piece[i][j] != '.') {
                    mnr = min(mnr, i), mxr = max(mxr, i), mnc = min(mnc, j), mxc = max(mxc, j);
                }
            }
        }
        vector<string> res(mxr - mnr + 1);
        for(int i = mnr; i <= mxr; i++) {
            for(int j = mnc; j <= mxc; j++) {
                res[i - mnr] += piece[i][j];
            }
        }
        return res;
    };
    auto dflip = [](vector<string> & piece) {
        int r = piece.size(), c = piece[0].length();
        vector<string> res(c);
        for(int i = 0; i < c; i++) {
            for(int j = 0; j < r; j++) {
                res[i] += piece[j][i];
            }
        }
        piece = res;
    };
    auto hflip = [](vector<string> & piece) {
        int r = piece.size(), c = piece[0].length();
        for(int i = 0; i < r; i++) {
            for(int j = 0, k = c - 1; j < k; j++, k--) {
                swap(piece[i][j], piece[i][k]);
            }
        }
    };
    auto vflip = [](vector<string> & piece) {
        int r = piece.size(), c = piece[0].length();
        for(int i = 0, j = r - 1; i < j; i++, j--) {
            for(int k = 0; k < c; k++) {
                swap(piece[i][k], piece[j][k]);
            }
        }
    };
    kr_hash zero;
    int k, n, m; cin >> k;
    vector<vector<string>> pieces(k + 1);
    for(int i = 0; i <= k; i++) {
        int r, c; cin >> r >> c;
        pieces[i] = read_piece(r, c);
    }
    n = pieces[0].size(), m = pieces[0][0].size();
    vector<PieceHasher> hash_info;
    unordered_map<kr_hash, int, kr_hash> shifted_piece;
    PieceHasher tot(pieces[0], m); kr_hash tot_hash = tot.hsh;
    vector<int> ct(k + 1, 0); vector<array<int, 3>> triples;
    for(int p = 1; p <= k; p++) {
        int id = p;
        for(int r1 = 0; r1 < 2; r1++, dflip(pieces[p])) {
            if(pieces[p].size() > n || pieces[p][0].length() > m) continue;
            for(int r2 = 0; r2 < 2; r2++, hflip(pieces[p])) {
                for(int r3 = 0; r3 < 2; r3++, vflip(pieces[p])) {
                    PieceHasher sh(pieces[p], 2 * m - (int) pieces[p][0].length(), p);
                    kr_hash full = (sh.hsh << ((2 * n - 1) * m - sh.lp));
                    if(shifted_piece.count(full)) {
                        id = shifted_piece[full];
                    } else {
                        hash_info.push_back(sh);
                        shifted_piece[full] = p;
                    }
                }
            }
        }
        ++ct[id], pieces[p].clear();
    }
    vector<int> cover_pieces(2), offset(2, -1);
    auto suffix_empty = [&zero, &tot, &hash_info, &cover_pieces, &offset](int len) {
        kr_hash h = tot.suffix(len);
        for(int p = 0; p < 2; p++) {
            if(offset[p] >= 0) {
                int suf_len = min(hash_info[cover_pieces[p]].padded_len, max(0, len - offset[p]));
                h = h - (hash_info[cover_pieces[p]].suffix(suf_len) << offset[p]);
            }
        }
        return h == zero;
    };
    auto last_piece = [&n, &m, &suffix_empty]() {
        int lb = 1, ub = (2 * n - 1) * m;
        while(lb < ub) {
            int mid = (lb + ub) / 2;
            if(suffix_empty(mid)) lb = mid + 1;
            else ub = mid;
        }
        return ub;
    };
    for(int i = 0; i < hash_info.size(); i++) {
        offset[0] = last_piece() - hash_info[i].lp;
        if(offset[0] < 0) continue;
        cover_pieces[0] = i;
        for(int j = 0; j < hash_info.size(); j++) {
            offset[1] = last_piece() - hash_info[j].lp;
            if(offset[1] < 0) continue;
            cover_pieces[1] = j;
            int lp3 = last_piece();
            kr_hash piece1 = hash_info[i].hsh, piece2 = hash_info[j].hsh;
            kr_hash res = (tot_hash - (piece1 << offset[0]) - (piece2 << offset[1])) << ((2 * n - 1) * m - lp3);
            if(shifted_piece.count(res)) {
                array<int, 3> cur = {hash_info[i].ind, hash_info[j].ind, shifted_piece[res]};
                sort(cur.begin(), cur.end()); triples.push_back(cur);
            }
            offset[1] = -1;
        }
        offset[0] = -1;
    }
    sort(triples.begin(), triples.end());
    triples.erase(unique(triples.begin(), triples.end()), triples.end());
    int ans = 0;
    for(auto [i, j, k]: triples) {
        if(i == k) {
            ans += ct[i] * (ct[i] - 1) * (ct[i] - 2) / 6;
        } else if(i == j || j == k) {
            ans += ct[i ^ j ^ k] * ct[j] * (ct[j] - 1) / 2;
        } else {
            ans += ct[i] * ct[j] * ct[k];
        }
    }
    cout << ans << '\n';
}