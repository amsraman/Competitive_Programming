#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, ct = 0; cin >> n;
    vector<string> words(n);
    map<char, int> lets;
    map<pair<int, int>, int> edges;
    for(int i = 0; i < n; i++) {
        cin >> words[i];
        if(!lets.count(words[i][0])) lets[words[i][0]] = ct++;
        if(!lets.count(words[i].back())) lets[words[i].back()] = ct++;
        ++edges[{lets[words[i][0]], lets[words[i].back()]}];
    }
    using state = tuple<int, int, int, bool, bool, bool>;
    map<state, bool> game;
    auto gen = [&](auto rec, state cur) -> bool {
        if(game.count(cur)) return game[cur];
        auto [bal1, bal2, bal3, par1, par2, par3] = cur;
        bool winning = false;
        if(bal1 > 0) {
            bool nxt = rec(rec, {bal2, bal3, bal1 - 1, par2, par3, par1});
            if(!nxt) winning = true;
        }
        if(par1 > 0) {
            bool nxt = rec(rec, {bal1, bal2, bal3, par1 - 1, par2, par3});
            if(!nxt) winning = true;
        }
        if(bal3 < 0) {
            bool nxt = rec(rec, {bal3 + 1, bal1, bal2, par3, par1, par2});
            if(!nxt) winning = true;
        }
        return game[cur] = winning;
    };
    int ans = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(edges[{i, j}] == 0) continue;
            --edges[{i, j}];
            state cur = {edges[{0, 1}] - edges[{1, 0}], edges[{1, 2}] - edges[{2, 1}], edges[{2, 0}] - edges[{0, 2}], edges[{0, 0}] % 2, edges[{1, 1}] % 2, edges[{2, 2}] % 2};
            for(int k = 0; k < j; k++) {
                auto [a, b, c, d, e, f] = cur;
                cur = {b, c, a, e, f, d};
            }
            ++edges[{i, j}];
            if(!gen(gen, cur)) ans += edges[{i, j}];
        }
    }
    cout << ans << '\n';
}