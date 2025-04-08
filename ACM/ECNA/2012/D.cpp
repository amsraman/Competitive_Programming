#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    vector<array<int, 6>> tups;
    array<int, 6> cur;
    auto gen = [&](auto rec, int lev, int left) -> void {
        if(lev == 6) {
            if(left == 0) {
                tups.push_back(cur);
            }
            return;
        }
        for(int i = 0; i <= left; i++) {
            cur[lev] = i;
            rec(rec, lev + 1, left - i);
        }
    };
    gen(gen, 0, 15);
    map<array<int, 6>, int> ind;
    for(int i = 0; i < (int) tups.size(); i++) {
        ind[tups[i]] = i;
    }
    char tp; cin >> tp;
    for(int _ = 1; tp != 'e'; _++) {
        if(tp == 'm') {
            array<int, 6> inp;
            for(int i = 0; i < 6; i++) {
                cin >> inp[i];
            }
            cout << "Case " << _ << ": " << ind[inp] << '\n';
        } else {
            int inde; cin >> inde;
            cout << "Case " << _ << ":";
            for(int i = 0; i < 6; i++) {
                cout << " " << tups[inde][i];
            }
            cout << '\n';
        }
        cin >> tp;
    }
}