#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int blk = 24, half_blk = 12;

int main() {
    ifstream cin("string_concatenation_input.txt");
    ofstream cout("out.txt");
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    auto rand_int = [&](int l, int r) {
        return uniform_int_distribution<int>(l, r)(rng);
    };
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, k; cin >> n >> k;
        vector<int> l(n);
        for(int i = 0; i < n; i++) {
            cin >> l[i];
        }
        cout << "Case #" << _ << ": ";
        if(n < blk) {
            vector<int> seen_sum(2e5 * n + 1, -1);
            int msk1 = -1, msk2 = -1;
            for(int i = 1; i < 1 << n; i++) {
                int sum = 0;
                for(int j = 0; j < n; j++) {
                    if((i >> j) & 1) sum += l[j];
                }
                if(seen_sum[sum] != -1) {
                    msk1 = seen_sum[sum], msk2 = i;
                    break;
                }
                seen_sum[sum] = i;
            }
            if(msk1 == -1) {
                cout << "Impossible" << endl;
            } else {
                cout << "Possible" << endl;
                int both = msk1 & msk2; msk1 ^= both, msk2 ^= both;
                for(int i = 0; i < n; i++) {
                    if((msk1 >> i) & 1) cout << i + 1 << " ";
                }
                cout << endl;
                for(int i = 0; i < n; i++) {
                    if((msk2 >> i) & 1) cout << i + 1 << " ";
                }
                cout << endl;
            }
            continue;
        }
        cout << "Possible" << endl;
        vector<int> inds(n), left, right;
        iota(inds.begin(), inds.end(), 0);
        vector<bool> vis_msk(1 << blk, false), vis_sum(blk * 2e5 + 1, false);
        vector<int> seen_msks, left_msk(1 << half_blk, 0), right_msk(1 << half_blk, 0);
        auto get_sum = [&](int msk) {
            return left_msk[msk & ((1 << half_blk) - 1)] + right_msk[msk >> half_blk];
        };
        for(int ptr = 0; ptr + blk - 1 < n;) {
            for(int i = 0; i < blk; i++) {
                swap(inds[ptr + i], inds[rand_int(ptr + i, n - 1)]);
            }
            for(int i = 0; i < half_blk; i++) {
                left_msk[1 << i] = l[inds[ptr + i]];
                right_msk[1 << i] = l[inds[ptr + i + half_blk]];
            }
            for(int i = 1; i < 1 << half_blk; i++) {
                int bt = i & -i;
                left_msk[i] = left_msk[i ^ bt] + left_msk[bt];
                right_msk[i] = right_msk[i ^ bt] + right_msk[bt];
            }
            int msk1 = -1, msk2 = -1;
            while(true) {
                int msk = rand_int(0, (1 << blk) - 1);
                while(vis_msk[msk]) {
                    msk = rand_int(0, (1 << blk) - 1);
                }
                if(vis_sum[get_sum(msk)]) {
                    msk1 = msk;
                    break;
                }
                vis_msk[msk] = vis_sum[get_sum(msk)] = true;
                seen_msks.push_back(msk);
            }
            int targ_sum = get_sum(msk1);
            for(int msk: seen_msks) {
                if(get_sum(msk) == targ_sum) {
                    msk2 = msk;
                    break;
                }
            }
            int both = msk1 & msk2, base = ptr; msk1 ^= both, msk2 ^= both;
            for(int i = 0; i < blk; i++) {
                if((msk1 >> i) & 1) {
                    left.push_back(inds[base + i]);
                    swap(inds[ptr++], inds[base + i]);
                }
                if((msk2 >> i) & 1) {
                    right.push_back(inds[base + i]);
                    swap(inds[ptr++], inds[base + i]);
                }
            }
            for(int msk: seen_msks) {
                vis_sum[get_sum(msk)] = false;
                vis_msk[msk] = false;
            }
            seen_msks.clear();
        }
        sort(left.begin(), left.end()); sort(right.begin(), right.end());
        auto set_sum = [&](vector<int> inds) {
            ll res = 0;
            for(int ind: inds) res += l[ind];
            return res;
        };
        assert(set_sum(left) == set_sum(right));
        for(int ind: left) {
            cout << ind + 1 << " ";
        }
        cout << endl;
        for(int ind: right) {
            cout << ind + 1 << " ";
        }
        cout << endl;
    }
}