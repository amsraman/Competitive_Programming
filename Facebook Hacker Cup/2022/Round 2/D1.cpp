#include <bits/stdc++.h>

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
    ifstream cin("worklife_balance_chapter_1_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, m;
        long long ans = 0;
        cin >> n >> m;
        vector<int> a(n);
        vector<FenwickTree<int>> ft(3, FenwickTree<int>(n));
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            ft[a[i] - 1].upd(i, 1);
        }
        for(int i = 0, x, y, z; i < m; i++) {
            cin >> x >> y >> z;
            --x;
            ft[a[x] - 1].upd(x, -1), a[x] = y, ft[a[x] - 1].upd(x, 1);
            int sum1 = 0, sum2 = 0;
            vector<int> ls(3), rs(3);
            for(int j = 0; j < 3; j++) {
                ls[j] = ft[j].qry(z - 1), rs[j] = ft[j].qry(z, n - 1);
                sum1 += (j + 1) * ls[j], sum2 += (j + 1) * rs[j];
            }
            if(sum1 > sum2) {
                for(int j = 0; j < 3; j++) {
                    swap(ls[j], rs[j]);
                }
                swap(sum1, sum2);
            }
            int two_diff = min({ls[0], rs[2], (sum2 - sum1) / 4});
            ls[0] -= two_diff, ls[2] += two_diff, rs[0] += two_diff, rs[2] -= two_diff;
            sum1 += 2 * two_diff, sum2 -= 2 * two_diff;
            int one_two = min({ls[0], rs[1], (sum2 - sum1) / 2});
            ls[0] -= one_two, ls[1] += one_two, rs[0] += one_two, rs[1] -= one_two;
            sum1 += one_two, sum2 -= one_two;
            int two_three = min({ls[1], rs[2], (sum2 - sum1) / 2});
            ls[1] -= two_three, ls[2] += two_three, rs[1] += two_three, rs[2] -= two_three;
            sum1 += two_three, sum2 -= two_three;
            if(sum1 == sum2) {
                ans += two_diff + one_two + two_three;
            } else {
                --ans;
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}