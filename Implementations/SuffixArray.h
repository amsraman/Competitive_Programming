#include <bits/stdc++.h>

using namespace std;

struct suffix_array {
    int n, sigma;
    string str;
    vector<int> suf_arr, kasai, lcp_rank;

    suffix_array(int n, int sigma): n(n), sigma(sigma), suf_arr(n), kasai(n), lcp_rank(n) {};

    int ctoi(char c) {
        if(c == '$') {
            return 0;
        }
        return 1 + (c - 'a');
    }

    void construct_from_string(string s) {
        int eq_classes = 1;
        ++n, str = s + '$';
        vector<int> cnt(max(n, sigma), 0), c(n), sa_next(n), c_next(n);
        suf_arr.resize(n);
        for(int i = 0; i < n; i++) {
            ++cnt[ctoi(str[i])];
        }
        for(int i = 1; i < cnt.size(); i++) {
            cnt[i] += cnt[i - 1];
        }
        for(int i = 0; i < n; i++) {
            suf_arr[--cnt[ctoi(str[i])]] = i;
        }
        c[suf_arr[0]] = 0;
        for(int i = 1; i < n; i++) {
            if(s[suf_arr[i - 1]] != s[suf_arr[i]]) {
                ++eq_classes;
            }
            c[suf_arr[i]] = eq_classes - 1;
        }
        for(int lvl = 0; (1 << lvl) < n; lvl++) {
            fill(cnt.begin(), cnt.begin() + eq_classes, 0);
            for(int i = 0; i < n; i++) {
                sa_next[i] = (suf_arr[i] - (1 << lvl) + n) % n;
                ++cnt[c[sa_next[i]]];
            }
            for(int i = 1; i < eq_classes; i++) {
                cnt[i] += cnt[i - 1];
            }
            for(int i = n - 1; i >= 0; i--) {
                suf_arr[--cnt[c[sa_next[i]]]] = sa_next[i];
            }
            c_next[suf_arr[0]] = 0, eq_classes = 1;
            for(int i = 1; i < n; i++) {
                pair<int, int> class1 = {c[suf_arr[i - 1]], c[(suf_arr[i - 1] + (1 << lvl)) % n]};
                pair<int, int> class2 = {c[suf_arr[i]], c[(suf_arr[i] + (1 << lvl)) % n]};
                eq_classes += (class1 != class2);
                c_next[suf_arr[i]] = eq_classes - 1;
            }
            swap(c, c_next);
        }
        suf_arr.erase(suf_arr.begin()), --n;
    }

    void construct_lcp() {
        vector<int> pos(n);
        for(int i = 0; i < n; i++) {
            pos[suf_arr[i]] = i;
        }
        int len = 0;
        for(int i = 0; i < n; i++) {
            if(pos[i] == n - 1) {
                len = kasai[n - 1] = 0;
                continue;
            }
            int j = suf_arr[pos[i] + 1];
            while(i + len < n && j + len < n && str[i + len] == str[j + len]) {
                ++len;
            }
            kasai[pos[i]] = len;
            len = max(0, len - 1);
        }
    }

    int lcp(int sf1, int sf2) {
        // return rmq of something
    }
};