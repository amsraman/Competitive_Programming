#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for(int _ = 1; _ <= n; _++) {
        int num_players; cin >> num_players;
        vector<queue<int>> decks(num_players + 1);
        vector<int> disc(num_players), ctr(num_players, 0);
        for(int i = 0; i < 52; i++) {
            int d; cin >> d;
            decks[0].push(d);
        }
        auto move = [&]() {
            for(int i = num_players - 1; i >= 0; i--) {
                if(!decks[i].empty()) {
                    int tp = decks[i].front(); decks[i].pop();
                    if(tp == ctr[i] % 13 + 1) {
                        disc[i] = tp;
                        decks[i + 1].push(tp);
                    } else {
                        decks[i].push(tp);
                    }
                    ++ctr[i];
                }
            }
        };
        for(int i = 0; i < 1e5; i++) {
            move();
        }
        cout << "Case " << _ << ":";
        if(decks[num_players].size() != 52) {
            cout << " unwinnable\n";
        } else {
            for(int i = 0; i < num_players; i++) {
                cout << " " << disc[i];
            }
            cout << '\n';
        }
    }
}