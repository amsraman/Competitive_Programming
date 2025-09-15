#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<pair<int, int>> rects;
    int area = 0;
    for(int i = 0, w, h; i < 4; i++) {
        cin >> w >> h;
        rects.emplace_back(w, h);
        area += w * h;
    }
    int side = sqrt(area);
    if(side * side != area) {
        cout << "0\n";
    } else {
        bool ans = false;
        sort(rects.begin(), rects.end());
        auto two_make_one = [](pair<int, int> r1, pair<int, int> r2, pair<int, int> r3) { // can r1 and r2 merge to r3?
            if(r1.second == r2.second && r1.second == r3.second && (r1.first + r2.first == r3.first)) { // vertical
                return true;
            }
            if((r1.second + r2.second == r3.second) && r1.first == r2.first && r1.first == r3.first) { // horizontal
                return true;
            }
            return false;
        };
        do {
            for(int i = 0; i < 16; i++) {
                for(int j = 0; j < 4; j++) {
                    if((i >> j) & 1) swap(rects[j].first, rects[j].second);
                }
                // observation: there must be a dividing line
                bool one = two_make_one(rects[0], rects[1], {side, rects[1].second});
                bool two = two_make_one(rects[2], rects[3], {side, side - rects[1].second});
                if(one && two) ans = true;
                one = two_make_one(rects[0], rects[1], {side, rects[0].second + rects[0].second});
                two = two_make_one(rects[2], rects[3], {side, side - rects[0].second - rects[1].second});
                if(one && two) ans = true;
                if(rects[0].first == side && (rects[0].second + rects[1].second == side) && two_make_one(rects[2], rects[3], {side - rects[1].first, rects[1].second})) {
                    ans = true;
                }
                for(int j = 0; j < 4; j++) {
                    if((i >> j) & 1) swap(rects[j].first, rects[j].second);
                }
            }
        } while(next_permutation(rects.begin(), rects.end()));
        cout << ans << '\n';
    }
}