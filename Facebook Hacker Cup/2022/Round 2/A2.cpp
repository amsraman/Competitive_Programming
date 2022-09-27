#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int num_hashes = 15;

template <typename T>
struct FenwickTree {
    size_t n;
    vector<T> bit;
    FenwickTree(size_t n): n(n), bit(n, 0) {};
    FenwickTree(int n, vector<T> & init): n(n), bit(n) {
        copy(init.begin(), init.end(), bit.begin());
        for(int i = 1; i <= n; i++) {
            if(i + (i & -i) <= n) {
                bit[i + (i & -i) - 1] += bit[i - 1];
            }
        }
    }
    T qry(int k) {
        T ret = 0;
        for(k++; k > 0; k -= k & -k) {
            ret += bit[k - 1];
        }
        return ret;
    }
    T qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }
    void upd(int k, T x) {
        for(k++; k <= n; k += k & -k) {
            bit[k - 1] += x;
        }
    }
};

int main() {
    ifstream cin("perfectly_balanced_chapter_2_input.txt");
    ofstream cout("output.txt");
    vector<vector<ll>> hsh(num_hashes, vector<ll>(1000001));
    vector<map<ll, int>> ihsh(num_hashes);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for(int i = 0; i < num_hashes; i++) {
        for(int j = 0; j <= 1000000; j++) {
            ll res = uniform_int_distribution<ll>(1, (1LL < 40) - 1)(rng);
            while(ihsh[i].count(res)) {
                res = uniform_int_distribution<ll>(1, (1LL << 40) - 1)(rng);
            }
            hsh[i][j] = res, ihsh[i][res] = j;
        }
    }
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, q, ans = 0;
        cin >> n;
        vector<int> a(n), ct(1000001, 0);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            ++ct[a[i]];
        }
        vector<FenwickTree<ll>> ft(num_hashes, FenwickTree<ll>(n));
        for(int i = 0; i < num_hashes; i++) {
            for(int j = 0; j < n; j++) {
                ft[i].upd(j, hsh[i][a[j]]);
            }
        }
        cin >> q;
        for(int i = 0, tp, x, y, l, r; i < q; i++) {
            cin >> tp;
            if(tp == 1) {
                cin >> x >> y;
                --x;
                for(int j = 0; j < num_hashes; j++) {
                    ll res = ft[j].qry(x, x);
                    ft[j].upd(x, -res), ft[j].upd(x, hsh[j][y]);
                }
                --ct[a[x]], a[x] = y, ++ct[y];
            } else {
                cin >> l >> r;
                --l, --r;
                if((r - l) & 1) {
                    continue;
                }
                int mid = ((l + r + 1) >> 1) - 1;
                bool ok1 = true, ok2 = true;
                for(int j = 0; j < num_hashes; j++) {
                    ll res = ft[j].qry(mid + 1, r) - ft[j].qry(l, mid);
                    if(!ihsh[j].count(res) || ct[ihsh[j][res]] == 0) {
                        ok1 = false;
                    }
                    res = ft[j].qry(l, mid + 1) - ft[j].qry(mid + 2, r);
                    if(!ihsh[j].count(res) || ct[ihsh[j][res]] == 0) {
                        ok2 = false;
                    }
                }
                ans += (ok1 || ok2);
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}