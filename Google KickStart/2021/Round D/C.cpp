#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t, n, m;
ll skill[100000];
pair<ll,ll> psets[100000];
set<pair<ll,ll>> cur_sets;

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n >> m;
        for(int i = 0; i < n; i++) {
            cin >> psets[i].f >> psets[i].s;
            cur_sets.insert(psets[i]);
        }
        cout << "Case #" << _ << ": ";
        for(int i = 0; i < m; i++) {
            cin >> skill[i];
            auto it = cur_sets.upper_bound({skill[i] + 1, -1});
            ll diff = (it == cur_sets.end() ? 2e18 : (it->f - skill[i]));
            if(it != cur_sets.begin() && ((skill[i] - (--it)->s) <= diff)) {
                pair<ll,ll> rem = *(--cur_sets.upper_bound({skill[i] + 1, -1}));
                cout << min(skill[i], rem.s) << " ";
                cur_sets.erase(rem);
                if(min(skill[i], rem.s) != rem.f) {
                    cur_sets.insert({rem.f, min(rem.s, skill[i]) - 1});
                }
                if(skill[i] < rem.s) {
                    cur_sets.insert({skill[i] + 1, rem.s});
                }
            } else {
                pair<ll,ll> rem = *cur_sets.upper_bound({skill[i] + 1, -1});
                cur_sets.erase(rem);
                cout << rem.f << " ";
                if(rem.f != rem.s) {
                    cur_sets.insert({rem.f + 1, rem.s});
                }
            }
        }
        cout << endl;
        cur_sets.clear();
    }
}