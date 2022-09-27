#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("perfectly_balanced_chapter_1_input.txt");
    ofstream cout("output.txt");
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        string s;
        cin >> s;
        int n = s.length(), q, ans = 0;
        vector<vector<int>> ps(n + 1, vector<int>(26, 0));
        for(int i = 0; i < n; i++) {
            ps[i + 1][s[i] - 'a'] = 1;
        }
        for(int i = 0; i < 26; i++) {
            for(int j = 1; j <= n; j++) {
                ps[j][i] += ps[j - 1][i];
            }
        }
        auto get_sum = [&](int l, int r, int ind) {
            return ps[r + 1][ind] - ps[l][ind];
        };
        cin >> q;
        for(int i = 0, l, r; i < q; i++) {
            cin >> l >> r;
            --l, --r;
            if((r - l) & 1) {
                continue;
            }
            int mid = ((l + r + 1) >> 1) - 1, nd1 = 0, nd2 = 0;
            bool ok1 = true, ok2 = true;
            for(int j = 0; j < 26; j++) {
                if(get_sum(l, mid, j) != get_sum(mid + 1, r, j)) {
                    ok1 &= (abs(get_sum(l, mid, j) - get_sum(mid + 1, r, j)) == 1);
                    ++nd1;
                }
                if(get_sum(l, mid + 1, j) != get_sum(mid + 2, r, j)) {
                    ok2 &= (abs(get_sum(l, mid + 1, j) - get_sum(mid + 2, r, j)) == 1);
                    ++nd2;
                }
            }
            ok1 &= (nd1 == 1), ok2 &= (nd2 == 1);
            ans += (int) (ok1 || ok2);
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}