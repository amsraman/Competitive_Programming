#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int l, c, n; cin >> l >> c >> n;
        vector<tuple<string, int, int>> prev_guesses;
        for(int i = 0; i < n; i++) {
            string g; int b, w; cin >> g >> b >> w;
            prev_guesses.emplace_back(g, b, w);
        }
        vector<string> tot, pos; vector<int> in(20);
        auto get_score = [&](string & ref, string & guess) -> pair<int, int> {
            int b = 0, w = 0;
            fill(in.begin(), in.end(), 0);
            for(int i = 0; i < l; i++) {
                if(ref[i] == guess[i]) {
                    ++b;
                } else {
                    ++in[ref[i] - 'A'];
                }
            }
            for(int i = 0; i < l; i++) {
                if(ref[i] != guess[i] && in[guess[i] - 'A'] > 0) {
                    ++w, --in[guess[i] - 'A'];
                }
            }
            return make_pair(b, w);
        };
        vector<int> cur(l);
        auto gen = [&](auto rec, int lev) -> void {
            if(lev == 0) {
                bool ok = true;
                string guess = "";
                for(int i: cur) guess += char('A' + i);
                tot.push_back(guess);
                for(int i = 0; i < n; i++) {
                    auto [s, b, w] = prev_guesses[i];
                    if(get_score(s, guess) != make_pair(b, w)) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    pos.push_back(guess);
                }
                return;
            }
            for(int i = 0; i < c; i++) {
                cur[l - lev] = i;
                rec(rec, lev - 1);
            }
        };
        gen(gen, l);
        pair<int, string> res = {1e9, ""};
        for(string guess: tot) {
            vector<vector<int>> num(15, vector<int>(15, 0));
            int uncertainty = 0;
            for(string corr: pos) {
                if(corr == guess) continue;
                auto [b, w] = get_score(corr, guess);
                ++num[b][w];
                if(num[b][w] > res.first) break;
                uncertainty = max(uncertainty, num[b][w]);
            }
            res = min(res, make_pair(uncertainty, guess));
        }
        auto [uncertainty, move] = res;
        cout << move << " " << uncertainty << '\n';
    }
}