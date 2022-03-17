#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int sq = 200;

int t, n, seen[200000];
pair<int, int> ans;
vector<int> sets[100000];
vector<pair<int, int>> vecs[200000];

bool solve() {
    vector<array<int, 3>> vals;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < sets[i].size(); j++) {
            vals.push_back({sets[i][j], i, j});
        }
    }
    sort(vals.begin(), vals.end());
    int sz = 0;
    for(int i = 0; i < vals.size(); i++) {
        sets[vals[i][1]][vals[i][2]] = sz;
        if(i + 1 == vals.size() || vals[i][0] != vals[i + 1][0]) {
            ++sz;
        }
    }
    for(int i = 0; i < sz; i++) {
        seen[i] = 0, vecs[i].clear();
    }
    vector<int> sm;
    for(int i = 0; i < n; i++) {
        if(sets[i].size() >= sq) {
            for(int j: sets[i]) {
                seen[j] = 1;
            }
            for(int j = 0; j < n; j++) {
                if(j != i) {
                    int ct = 0;
                    for(int k: sets[j]) {
                        if(seen[k]) {
                            ++ct;
                            if(ct == 2) {
                                ans = {i + 1, j + 1};
                                return true;
                            }
                        }
                    }
                }
            }
            for(int j: sets[i]) {
                seen[j] = 0;
            }
        } else {
            sm.push_back(i);
        }
    }
    for(int i: sm) {
        for(int j: sets[i]) {
            for(int k: sets[i]) {
                if(j != k) {
                    vecs[j].push_back({k, i});
                }
            }
        }
    }
    for(int i = 0; i < sz; i++) {
        for(pair<int, int> j: vecs[i]) {
            seen[j.f] = 0;
        }
        for(pair<int, int> j: vecs[i]) {
            if(seen[j.f] > 0) {
                ans = {seen[j.f], j.s + 1};
                return true;
            }
            seen[j.f] = j.s + 1;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0, k; i < n; i++) {
            cin >> k;
            sets[i].resize(k);
            for(int j = 0; j < k; j++) {
                cin >> sets[i][j];
            }
        }
        if(solve()) {
            cout << ans.f << " " << ans.s << '\n';
        } else {
            cout << "-1\n";
        }
    }
}