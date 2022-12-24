#include <bits/stdc++.h>

using namespace std;

const int num_hashes = 3; // worth a shot I guess

template <class B>
struct SegTree : public B {
    using T = typename B::T;
    int n, sz, log;
    vector<T> seg;
    SegTree(int n): n(n), log(__lg(max(n - 1, 1)) + 1) {
        sz = (1 << log), seg.resize(sz << 1, B::e);
    };
    SegTree(vector<T> & init): n((int) init.size()), log(__lg(max(n - 1, 1)) + 1) {
        sz = (1 << log), seg.resize(sz << 1, B::e);
        copy(init.begin(), init.end(), seg.begin() + sz);
        for(int i = sz - 1; i > 0; i--) {
            seg[i] = B::comb(seg[2 * i], seg[2 * i + 1]);
        }
    };
    T qry(int lo, int hi) {
        T ret1 = B::e, ret2 = B::e;
        for(lo += sz, hi += sz; lo <= hi; lo >>= 1, hi >>= 1) {
            if(lo & 1) {
                ret1 = B::comb(ret1, seg[lo++]);
            }
            if(hi & 1 ^ 1) {
                ret2 = B::comb(seg[hi--], ret2);
            }
        }
        return B::comb(ret1, ret2);
    }
    void upd(int ind, T val) {
        seg[ind += sz] = val;
        while(ind > 1) {
            ind >>= 1;
            seg[ind] = B::comb(seg[2 * ind], seg[2 * ind + 1]);
        }
    }
};

struct Mon {
    using T = array<long long, num_hashes>;
    const T e = {0, 0, 0};
    T comb(T a, T b) {
        for(int i = 0; i < num_hashes; i++) {
            a[i] += b[i];
        }
        return a;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n, q; cin >> n >> q;
    vector<int> a(n), uni;
    vector<array<long long, num_hashes>> hsh_val(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i]; uni.push_back(a[i]);
    }
    sort(uni.begin(), uni.end()); uni.erase(unique(uni.begin(), uni.end()), uni.end());
    for(int i = 0; i < num_hashes; i++) {
        map<int, long long> hsh;
        set<long long> used;
        for(int j = 0; j < uni.size(); j++) {
            long long rd = uniform_int_distribution<long long>(0, 1e18)(rng);
            while(used.count(rd)) {
                rd = uniform_int_distribution<long long>(0, 1e12)(rng);
            }
            hsh[uni[j]] = rd, used.insert(rd);
        }
        for(int j = 0; j < n; j++) {
            hsh_val[j][i] = hsh[a[j]];
        }
    }
    vector<vector<pair<int, int>>> q1(n), q2(n);
    vector<array<long long, num_hashes>> res1(q), res2(q);
    map<array<long long, num_hashes>, int> lst;
    for(int i = 0, l1, l2, r1, r2; i < q; i++) {
        cin >> l1 >> r1 >> l2 >> r2;
        q1[r1 - 1].push_back({l1 - 1, i});
        q2[r2 - 1].push_back({l2 - 1, i});
    }
    SegTree<Mon> st(n);
    for(int i = 0; i < n; i++) {
        if(lst.count(hsh_val[i])) {
            st.upd(lst[hsh_val[i]], {0, 0, 0});
        }
        lst[hsh_val[i]] = i;
        st.upd(i, hsh_val[i]);
        for(auto [l, ind]: q1[i]) {
            res1[ind] = st.qry(l, i);
        }
        for(auto [l, ind]: q2[i]) {
            res2[ind] = st.qry(l, i);
        }
    }
    for(int i = 0, l1, l2, r1, r2; i < q; i++) {
        cout << (res1[i] == res2[i] ? "YES" : "NO") << '\n';
    }
}