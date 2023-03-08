// 1666 ms
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q, node_count = 0; cin >> q;
    vector<int> cnt(30 * q, 0);
    vector<vector<int>> trie(30 * q, vector<int>(2, 0));
    auto ins = [&](int x, int sg) {
        int cur = 0;
        for(int i = 29; i >= 0; i--) {
            int side = (x >> i) & 1;
            if(!trie[cur][side]) {
                trie[cur][side] = ++node_count;
            }
            cur = trie[cur][side];
        }
        if(sg == cnt[cur]) {
            return;
        }
        cur = 0;
        for(int i = 29; i >= 0; i--) {
            int side = (x >> i) & 1;
            cur = trie[cur][side], cnt[cur] += (sg ? 1 : -1);
        }
    };
    auto qry = [&](int x) {
        int ret = 0, cur = 0;
        for(int i = 29; i >= 0; i--) {
            int side = (x >> i) & 1;
            if(trie[cur][side] && cnt[trie[cur][side]]) {
                cur = trie[cur][side];
            } else {
                ret ^= (1 << i), cur = trie[cur][side ^ 1];
            }
        }
        return ret;
    };
    for(int i = 0, type, x; i < q; i++) {
        cin >> type >> x;
        if(type == 0) {
            ins(x, 1);
        } else if(type == 1) {
            ins(x, 0);
        } else {
            cout << qry(x) << '\n';
        }
    }
}