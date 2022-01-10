#include <bits/stdc++.h>

using namespace std;

int n, id[101000], num[1000], tot, ans;
string s[1000], comb;

void ins(int x) {
    if(x < 0) {
        return;
    }
    ++num[x], tot += (num[x] == 1);
}

void rem(int x) {
    if(x < 0) {
        return;
    }
    --num[x], tot -= (num[x] == 0);
}

struct SuffixArray {
    const int sigma = 27;

    int n;
    string str;
    vector<int> suf_arr, suf_pos, kasai;
    vector<vector<int>> rmq;

    SuffixArray(int n, string str): n(n), str(str), suf_arr(n), suf_pos(n), kasai(n) {
        int eq_classes = 1;
        ++n, str += '$';
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
            if(str[suf_arr[i - 1]] != str[suf_arr[i]]) {
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
        for(int i = 0; i < n; i++) {
            suf_pos[suf_arr[i]] = i;
        }
        construct_lcp();
    };

    int ctoi(char c) {
        if(c == '$') {
            return 0;
        }
        return 1 + (c - 'a');
    }

    void construct_lcp() {
        int len = 0;
        for(int i = 0; i < n; i++) {
            if(suf_pos[i] == n - 1) {
                len = kasai[n - 1] = 0;
                continue;
            }
            int j = suf_arr[suf_pos[i] + 1];
            while(i + len < n && j + len < n && str[i + len] == str[j + len]) {
                ++len;
            }
            kasai[suf_pos[i]] = len;
            len = max(0, len - 1);
        }
        rmq.resize(n, vector<int>(__lg(n) + 1));
        for(int i = 0; i < n; i++) { 
            rmq[i][0] = kasai[i];
        }
        for(int i = 1; i <= __lg(n); i++) {
            for(int j = 0; j < n; j++) {
                rmq[j][i] = min(rmq[j][i - 1], rmq[min(n - 1, j + (1 << (i - 1)))][i - 1]);
            }
        }
    }

    int lcp(int sf1, int sf2) {
        if(sf1 == sf2) { 
            return n - sf1;
        }
        int pos1 = suf_pos[sf1], pos2 = suf_pos[sf2];
        if(pos1 > pos2) {
            swap(pos1, pos2);
        }
        int lv = __lg(pos2 - pos1);
        return min(rmq[pos1][lv], rmq[pos2 - (1 << lv)][lv]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> s[i];
        comb += s[i];
        if(i < n - 1) {
            comb += '$';
        }
    }
    for(int i = 0, j = 0; i < comb.length(); i++) {
        if(comb[i] == '$') {
            id[i] = -1, ++j;
        } else {
            id[i] = j;
        }
    }
    SuffixArray sa(comb.length(), comb);
    vector<int> suf = sa.suf_arr;
    for(int i = n - 1, j = 0; i < suf.size(); i++) {
        while(j < suf.size() && tot < n) {
            ins(id[suf[j]]);
            ++j;
        }
        if(tot == n) {
            ans = max(ans, sa.lcp(suf[i], suf[j - 1]));
        }
        rem(id[suf[i]]);
    }
    cout << ans << '\n';
}