#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("line_of_delivery_part_1_input.txt");
    ofstream cout("out.txt");
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, g; cin >> n >> g;
        vector<int> e(n); vector<pair<int, int>> srt;
        for(int i = 0; i < n; i++) {
            cin >> e[i]; srt.emplace_back(e[i], i);
        }
        sort(srt.begin(), srt.end()); int ans1 = 1e9, ans2 = 1e9;
        for(int i = 0; i < n; i++) {
            ans2 = min(ans2, abs(g - e[i]));
        }
        auto get_ind = [&](int pl, int tm) {
            set<int> left, places; int ptr1 = n - 1, ptr2 = n - 1;
            for(int i = 0; i < n; i++) {
                places.insert(e[i]);
            }
            while(true) {
                while(ptr1 >= 0 && srt[ptr1].first >= pl) {
                    left.insert(srt[ptr1].second);
                    --ptr1;
                }
                auto it = left.upper_bound(tm);
                assert(it != left.begin());
                --it; tm = *it;
                while(ptr2 > tm) {
                    places.erase(e[ptr2]); --ptr2;
                }
                it = places.lower_bound(pl);
                if(it == places.begin()) {
                    return tm + 1;
                    break;
                }
                --it;
                pl = *it; --tm;
            }
        };
        for(int i = 0; i < n; i++) {
            if(abs(e[i] - g) == ans2) {
                ans1 = min(ans1, get_ind(e[i], n - 1));
            }
        }
        cout << "Case #" << _ << ": " << ans1 << " " << ans2 << '\n';
    }
}
/*
who is at my position?

*/