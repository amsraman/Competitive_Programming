#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for(int _ = 1; n > 0; _++) {
        string faces, turns; cin >> faces >> turns;
        deque<deque<pair<int, char>>> decks(n);
        for(int i = 0; i < n; i++) {
            decks[i].emplace_back(i + 1, faces[i]);
        }
        for(int i = 0; i < n - 1; i++) {
            if(turns[i] == 'L') {
                while(!decks[0].empty()) {
                    auto [num, dir] = decks[0].front(); decks[0].pop_front();
                    decks[1].emplace_front(num, dir ^ 'U' ^ 'D');
                }
                decks.pop_front();
            } else {
                int sz = decks.size();
                while(!decks[sz - 1].empty()) {
                    auto [num, dir] = decks[sz - 1].front(); decks[sz - 1].pop_front();
                    decks[sz - 2].emplace_front(num, dir ^ 'U' ^ 'D');
                }
                decks.pop_back();
            }
        }
        int m; cin >> m;
        cout << "Pile " << _ << '\n';
        for(int i = 0, q; i < m; i++) {
            cin >> q; --q;
            auto [num, dir] = decks[0][q];
            cout << "Card " << q + 1 << " is a face " << (dir == 'U' ? "up " : "down ") << num << ".\n";
        }
        cin >> n;
    }
}