#include <bits/stdc++.h>

using namespace std;

int n, s;
map<int, int> m[2];
vector<pair<int, int>> vb, vs;

int main() {
    cin >> n >> s;
    for(int i = 0, p, q; i < n; i++) {
        char tp;
        cin >> tp >> p >> q;
        if(tp == 'B') {
            m[0][p] += q;
        } else {
            m[1][p] += q;
        }
    }
    for(auto it: m[0]) {
        vb.push_back(it);
    }
    for(auto it: m[1]) {
        vs.push_back(it);
    }
    sort(vb.begin(), vb.end());
    reverse(vb.begin(), vb.end());
    sort(vs.begin(), vs.end());
    reverse(vs.begin(), vs.end());
    for(int i = max(0, (int) vs.size() - s); i < vs.size(); i++) {
        cout << "S " << vs[i].first << " " << vs[i].second << '\n';
    }
    for(int i = 0; i < min(s, (int) vb.size()); i++) {
        cout << "B " << vb[i].first << " " << vb[i].second << '\n';
    }
}