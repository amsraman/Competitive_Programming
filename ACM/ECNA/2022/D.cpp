#include <bits/stdc++.h>

using namespace std;

int main() {
    string dna; cin >> dna;
    int len = (int) dna.length();
    vector<vector<int>> ps(len + 1, vector<int>(4, 0));
    auto get_rank = [](char c) {
        if(c == 'A') return 0;
        if(c == 'T') return 1;
        if(c == 'G') return 2;
        return 3;
    };
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < 4; j++) {
            ps[i + 1][j] = ps[i][j];
        }
        ++ps[i + 1][get_rank(dna[i])];
    }
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int s, e; cin >> s >> e; --s;
        string res = "ATCG";
        sort(res.begin(), res.end(), [&](char x, char y) {
            int r1 = get_rank(x), r2 = get_rank(y);
            int f1 = ps[e][r1] - ps[s][r1], f2 = ps[e][r2] - ps[s][r2];
            return make_pair(-f1, r1) < make_pair(-f2, r2);
        });
        cout << res << '\n';
    }
}