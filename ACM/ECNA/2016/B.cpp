#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, ct = 0; cin >> n;
    map<string, int> ind;
    vector<string> ref;
    for(int i = 0; i < n; i++) {
        string p; cin >> p; ind[p] = ct++;
        ref.push_back(p);
    }
    string rec; cin >> rec;
    int m = (int) rec.length();
    int lw = -1, lb = -1;
    vector<pair<int, int>> winners; int bst = -1;
    int wo = 0, bo = 1, wd = 2, bd = 3;
    queue<int> line; vector<int> lst(n, 0);
    for(int i = 4; i < n; i++) line.push(i);
    auto add_streak = [&](int st, int w1, int w2) {
        if(lst[w1] > lst[w2]) swap(w1, w2);
        if(lst[w1] == 0 && lst[w2] == 0 && w1 > w2) swap(w1, w2);
        if(st < bst) return;
        if(st > bst) {
            bst = st; winners.clear();
        }
        winners.emplace_back(w1, w2);
    };
    for(int i = 0; i < m; i++) {
        if(rec[i] == 'B') {
            add_streak(i - lw, wo, wd); lw = i;
            swap(bo, bd);
            line.push(wd); wd = wo;
            wo = line.front(); line.pop();
            lst[wo] = i;
        } else {
            add_streak(i - lb, bo, bd); lb = i;
            swap(wo, wd);
            line.push(bd); bd = bo;
            bo = line.front(); line.pop();
            lst[bo] = i;
        }
    }
    add_streak(m - lw, wo, wd);
    add_streak(m - lb, bo, bd);
    for(auto [i, j]: winners) {
        cout << ref[i] << " " << ref[j] << '\n';
    }
}