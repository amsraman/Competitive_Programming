#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ifstream cin("sum_41_chapter_1_input.txt");
    ofstream cout("output.txt");
    ll prod = 1;
    vector<int> cur;
    map<ll, vector<int>> seq;
    auto gen = [&](auto rec, int lim, int left) {
        if(left == 0) {
            if(!seq.count(prod) || cur.size() < seq[prod].size()) {
                seq[prod] = cur;
            }
            return;
        }
        if(lim > left) return;
        for(int i = lim; i <= left; i++) {
            prod *= i; cur.push_back(i);
            rec(rec, i, left - i);
            prod /= i; cur.pop_back();
        }
    };
    gen(gen, 1, 41);
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int p; cin >> p;
        cout << "Case #" << _ << ": ";
        if(seq.count(p)) {
            auto res = seq[p];
            cout << res.size();
            for(int r: res) {
                cout << " " << r;
            }
            cout << '\n';
        } else {
            cout << "-1\n";
        }
    }
}