#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

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
    ifstream cin("worklife_balance_chapter_2_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m;
        ll ans = 0;
        cin >> n >> m;
        vector<int> a(n);
        vector<FenwickTree<int>> num(2, FenwickTree<int>(n));
        vector<FenwickTree<ll>> sum(2, FenwickTree<ll>(n));
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            --a[i], num[a[i]].upd(i, 1), sum[a[i]].upd(i, i);
        }
        for(int i = 0, x, y, z; i < m; i++) {
            cin >> x >> y >> z;
            --x, --y, --z;
            num[a[x]].upd(x, -1), sum[a[x]].upd(x, -x);
            a[x] = y;
            num[a[x]].upd(x, 1), sum[a[x]].upd(x, x);
            int sum1 = num[1].qry(z) + z + 1, sum2 = num[1].qry(z + 1, n - 1) + n - z - 1;
            if((sum1 ^ sum2) & 1) {
                --ans; // parity differs, quit
                continue;
            }
            int to_add = (sum1 <= sum2), num_add = abs(sum1 - sum2) / 2;
            if(num[to_add].qry(z + 1, n - 1) < num_add || num[to_add ^ 1].qry(z) < num_add) {
                --ans; // not enough to add, quit
                continue;
            }
            if(sum1 == sum2) {
                continue; // already good, quit
            }
            int lb = 0, ub = z, pf, sf;
            while(lb < ub) {
                int mid = (lb + ub + 1) / 2;
                if(num[to_add ^ 1].qry(mid, z) >= num_add) {
                    lb = mid;
                } else {
                    ub = mid - 1;
                }
            }
            sf = ub, lb = z + 1, ub = n - 1;
            while(lb < ub) {
                int mid = (lb + ub) / 2;
                if(num[to_add].qry(z + 1, mid) >= num_add) {
                    ub = mid;
                } else {
                    lb = mid + 1;
                }
            }
            pf = ub;
            ans += sum[to_add].qry(sf, pf) - 1LL * (sf + z) * (z - sf + 1) / 2;
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}