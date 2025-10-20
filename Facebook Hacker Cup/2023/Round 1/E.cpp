#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <typename T, bool close>
struct Mo {
    using ord_t = pair<int, int>;
    using F = function<void (int)>;
    using G = function<T (void)>;
    const static int blk = 500;
    static ord_t order(int x, int y, int pow, int rotate) {
        return {x / blk, y};
    }
    static vector<T> solve_queries(vector<pair<int, int>> & query_list, F extend, F contract, G retrieve_ans) {
        return solve_queries(query_list, extend, extend, contract, contract, retrieve_ans);
    }
    static vector<T> solve_queries(vector<pair<int, int>> & query_list, F extend_left, F extend_right, F contract_left, F contract_right, G retrieve_ans) {
        int q = query_list.size();
        vector<tuple<ord_t, int, int, int>> sorted_queries;
        vector<T> res(q);
        for(int i = 0; i < q; i++) {
            auto [l, r] = query_list[i];
            sorted_queries.emplace_back(order(l, r, 20, 0), l, r, i);
        }
        sort(sorted_queries.begin(), sorted_queries.end());
        int cur_l = 0, cur_r = -1;
        int ct = 0, tot_sz = (int) sorted_queries.size();
        for(auto [_, l, r, ind]: sorted_queries) {
            while(cur_l > l) extend_left(--cur_l);
            while(cur_r < r) extend_right(++cur_r);
            while(cur_l < l) contract_left(cur_l++);
            while(cur_r > r) contract_right(cur_r--);
            assert(cur_l == l && cur_r == r);
            res[ind] = retrieve_ans();
        }
        if(close) {
            for(int i = cur_l; i <= cur_r; i++) contract_left(i);
        }
        return res;
    }
};

int main() {
    ifstream cin("bohemian_rapsody_input.txt");
    ofstream cout("output.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n; cin >> n;
        vector<vector<int>> w(n), dead;
        vector<vector<pair<int, int>>> qrs;
        vector<map<char, int>> trie(1); int nc = 0;
        for(int i = 0; i < n; i++) {
            string s; cin >> s; reverse(s.begin(), s.end());
            while((int) s.length() > (int) dead.size()) dead.emplace_back(), qrs.emplace_back();
            int cur = 0; dead[(int) s.length() - 1].push_back(i);
            for(char c: s) {
                if(!trie[cur].count(c)) {
                    trie[cur][c] = ++nc;
                    trie.emplace_back();
                }
                w[i].push_back(cur = trie[cur][c]);
            }
        }
        int q; cin >> q;
        for(int i = 0, a, b, k; i < q; i++) {
            cin >> a >> b >> k; --a, --b;
            if(k > (int) qrs.size()) continue;
            qrs[k - 1].emplace_back(a, b);
        }
        ll ans = 0;
        set<int> active;
        vector<int> str_ct(nc + 1, 0), val(n), num_at_ct(n, 0);
        int num_strs = 0;
        auto extend = [&](int ind) {
            if(str_ct[val[ind]] != 0) {
                --num_at_ct[str_ct[val[ind]] - 1];
            } else {
                ++num_strs;
            }
            ++str_ct[val[ind]];
            ++num_at_ct[str_ct[val[ind]] - 1];
        };
        auto contract = [&](int ind) {
            --num_at_ct[str_ct[val[ind]] - 1];
            --str_ct[val[ind]];
            if(str_ct[val[ind]] != 0) {
                ++num_at_ct[str_ct[val[ind]] - 1];
            } else {
                --num_strs;
            }
        };
        auto get_ans = [&]() {
            int ans = 0, avail = num_strs, over = 0;
            while(avail > 0) {
                int now = num_at_ct[ans++], take = min(now, over);
                now -= take, over -= take;
                if(now == 0) --avail, ++over;
                avail -= now;
            }
            return ans;
        };
        for(int i = -1; i <= n; i++) active.insert(i);
        for(int i = 0; i < (int) qrs.size(); i++) {
            vector<pair<int, int>> ranges;
            vector<int> indices_left;
            for(int ind: active) {
                if(ind >= 0 && ind < n) {
                    val[indices_left.size()] = w[ind][i];
                    indices_left.push_back(ind);
                }
            }
            for(auto [l, r]: qrs[i]) {
                l = *active.lower_bound(l);
                r = *--active.upper_bound(r);
                if(l == -1 || r == n || l > r) continue;
                l = lower_bound(indices_left.begin(), indices_left.end(), l) - indices_left.begin();
                r = lower_bound(indices_left.begin(), indices_left.end(), r) - indices_left.begin();
                ranges.emplace_back(l, r);
            }
            auto res = Mo<int, true>::solve_queries(ranges, extend, contract, get_ans);
            for(auto r: res) ans += r;
            for(int ind: dead[i]) { // kill strings
                active.erase(ind);
            }
        }
        cout << "Case #" << _ << ": " << ans << '\n';
    }
}