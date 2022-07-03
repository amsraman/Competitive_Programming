#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    string s;
    cin >> n >> q >> s;
    set<pair<int, int>> in;
    multiset<int> streaks;
    for(int i = 0, j = 0; i < n; i++) {
        if(i == n - 1 || s[i] != s[i + 1]) {
            in.insert({j, i}), streaks.insert(i - j + 1);
            j = i + 1;
        }
    }
    auto flip = [&](int x) {
        if(x < 0) {
            return;
        }
        auto it = --in.lower_bound({x, n + 1});
        pair<int, int> cur = *it;
        if(x != cur.s) {
            streaks.erase(streaks.find(cur.s - cur.f + 1));
            streaks.insert(x - cur.f + 1), streaks.insert(cur.s - x);
            in.insert({cur.f, x}), in.insert({x + 1, cur.s}), in.erase(cur);
        } else if(x != n - 1) {
            pair<int, int> nxt = *next(it);
            streaks.erase(streaks.find(cur.s - cur.f + 1)), streaks.erase(streaks.find(nxt.s - nxt.f + 1));
            streaks.insert(nxt.s - cur.f + 1);
            in.erase(cur), in.erase(nxt), in.insert({cur.f, nxt.s});
        }
    };
    for(int i = 0, t, l, r; i < q; i++) {
        cin >> t >> l >> r;
        flip(l - 2), flip(r - 1);
        cout << *--streaks.end() << '\n';
    }
}
// Didn't do this using a treap but whatever :)