#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int nt, ns, rmax; cin >> nt >> ns >> rmax;
    vector<pair<int, int>> trees, obs; vector<vector<int>> exists(2001, vector<int>(2001, 0));
    for(int i = 0; i < nt; i++) {
        int x, y; cin >> x >> y; trees.emplace_back(x, y);
    }
    for(int i = 0; i < ns; i++) {
        int x, y; cin >> x >> y; obs.emplace_back(x, y);
    }
    vector<pair<int, int>> works;
    auto try_source = [&](pair<int, int> src) {
        int num_here = 0;
        for(int i = 0; i < nt; i++) {
            pair<int, int> dif = make_pair(trees[i].first - src.first, trees[i].second - src.second);
            if(abs(dif.first) + abs(dif.second) > rmax) continue;
            dif.first += rmax, dif.second += rmax;
            if(exists[dif.first][dif.second] == 0) return;
            ++num_here; --exists[dif.first][dif.second];
        }
        if(num_here != ns) return;
        works.push_back(src);
    };
    for(int it = 0; it < 4; it++) {
        set<pair<int, int>> srcs;
        for(int i = 0; i < nt; i++) {
            srcs.insert(make_pair(trees[i].first - obs[0].first, trees[i].second - obs[0].second));
        }
        for(auto src: srcs) {
            for(int i = 0; i < ns; i++) {
                ++exists[obs[i].first + rmax][obs[i].second + rmax];
            }
            try_source(src);
            for(int i = 0; i < ns; i++) {
                exists[obs[i].first + rmax][obs[i].second + rmax] = 0;
            }
        }
        for(int i = 0; i < ns; i++) {
            obs[i] = make_pair(-obs[i].second, obs[i].first);
        }
    }
    bool same = false;
    for(int i = 0; i < ns; i++) {
        if(obs[i] == make_pair(0, 0)) {
            same = true;
        }
    }
    if(works.empty() || same) {
        cout << "Impossible\n";
    } else if(works.size() > 1) {
        cout << "Ambiguous\n";
    } else {
        auto [x, y] = works[0];
        cout << x << " " << y << '\n';
    }
}
/*
Mistakes:
- Capitalization
- Trees don't have to be distinct
- Multiple orientations can't work
- Various misreadings
- I'm just being clumsy at this point i don't give a fuck about this problem lol
*/