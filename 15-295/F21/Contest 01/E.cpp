#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t, n, q, sgn[300000], ps[300001];
set<pair<int, int>> sps[2];
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> q >> s;
        for(int i = 0; i < n; i++) {
            sgn[i] = ((i % 2 == 0) ? 1 : -1) * ((s[i] == '+') ? 1 : -1);
            ps[i + 1] = ps[i] + sgn[i];
            if(sgn[i] == 1) {
                sps[0].insert({ps[i], i});
            } else {
                sps[1].insert({ps[i], i});
            }
        }
        for(int i = 0, l, r; i < q; i++) {
            cin >> l >> r;
            if(ps[r] == ps[l - 1]) {
                cout << 0 << '\n';
                continue;
            }
            cout << 2 - (r - l + 1) % 2 << '\n';
            if((r - l + 1) % 2 == 0) {
                cout << l << " ";
                ++l;
            }
            int diff = ps[r] - ps[l - 1];
            auto it = sps[0].lower_bound({ps[l - 1] + (diff - 1) / 2, l - 1});
            if(it != sps[0].end() && it->f == ps[l - 1] + (diff - 1) / 2 && it->s < r) {
                cout << it->s + 1 << '\n';
                continue;
            }
            it = sps[1].lower_bound({ps[l - 1] + (diff + 1) / 2, l - 1});
            assert(it != sps[1].end());
            cout << it->s + 1 << '\n';
        }
        sps[0].clear(), sps[1].clear();
    }
}